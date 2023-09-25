/**
 * ATCA IO CONTROL Integrator
 * Project Name:   ATCA DAQ
 * Design Name:    ATCA-MIMO-DAQ Streaming  Linux Device Driver
 * PCI Device Id: 24
 * FW Version A
 * working with kernel 5.x.x
 *
 * Copyright 2023 - 2023 IPFN-Instituto Superior Tecnico, Portugal
 * Creation Date  2023-09-19
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they
 * will be approved by the European Commission - subsequent
 * versions of the EUPL (the "Licence");
 * You may not use this work except in compliance with the
 * Licence.
 * You may obtain a copy of the Licence at:
 *
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the Licence is
 * distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the Licence for the specific language governing
 * permissions and limitations under the Licence.
 *
 */
#include <linux/module.h>
#include <linux/pci.h>

//#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/delay.h>
//#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>

#include "pci-atca-adc.h"
#include "pci-atca-adc-ioctl.h"

/* Check macros and kernel version first */
#ifndef KERNEL_VERSION
#error "No KERNEL_VERSION macro! Stopping."
#endif

#ifndef LINUX_VERSION_CODE
#error "No LINUX_VERSION_CODE macro! Stopping."
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,9,0)
#error "This driver has been tested only for Kernel 5.x or above."
#endif

/*
 * Global variables
 */
int device_major = 0;
struct class* atca_ioc_class;

static int firmwareRevision   = 0;
static int current_board      = 0; // -1;
//#define CHAR_DEVICE_NAME            "pcieATCAAdc"
//static int master_board_index = -1;
//static int DMA_NBYTES         = 0;
static int dma_n_bytes         = 0;
// Global DMA address
//int DMA_global_addr[MAX_BOARDS * DMA_BUFFS];

// DAC locations
int DAC_addr[MAX_DEVICES * N_DACS_PER_BOARDS];

// DIO locations
int DIO_addr[MAX_DEVICES * N_DIOS_PER_BOARD];

// Command register locations (in order to export the enable and disable acquisition function)
//int command_register_addr[MAX_BOARDS];

// Status register locations
//int status_register_addr[MAX_BOARDS];

// The slot numbers for each of the board indexes
//int board_slot_numbers[MAX_BOARDS];

/*   Function prototypes          */
long pci_atca_adc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
/*
static int SlotNumberToBoardIndex(int slotNum) {
    int i = 0;
    for (i = 0; i < MAX_DEVICES; i++) {
        if (board_slot_numbers[i] == slotNum) {
            return i;
        }
    }
    return -1;
}
*/
//****************************
//* DMA management functions *
//****************************
//
static struct pci_device_id ids[] = {
    { PCI_DEVICE(PCI_VENDOR_ID_XILINX, PCI_DEVICE_ID_FPGA_ATCA), },
    { 0, }
};
MODULE_DEVICE_TABLE(pci, ids);

int atca_configure_pci(PCIE_DEV *pcieDev) {
    u16 reg16 = 0;
    int i = 0;
    int ret = 0;

    //set command register
    pci_read_config_word(pcieDev->pdev, PCI_COMMAND, &reg16);
    PDEBUG("%s pci_config word 0x%04X.\n", DRV_NAME, reg16);
    // printk(KERN_DEBUG "%s pci_config word 0x%04X.\n", DRV_NAME, reg16);
    reg16 &= ~PCI_COMMAND_IO; // disable IO port access
    reg16 |= PCI_COMMAND_PARITY; // enable parity error hangs
    reg16 |= PCI_COMMAND_SERR; // enable addr parity error
    pci_write_config_word(pcieDev->pdev, PCI_COMMAND, reg16);

    //PCI reading IO memory spaces and set virtual addresses
    for (i = 0; i < NUM_BARS; i++) {
        pcieDev->memIO[i].start = pci_resource_start(pcieDev->pdev, i);
        pcieDev->memIO[i].end = pci_resource_end(pcieDev->pdev, i);
        pcieDev->memIO[i].len = pci_resource_len(pcieDev->pdev, i);
        pcieDev->memIO[i].flags = pci_resource_flags(pcieDev->pdev, i);
        // virtual addr
        pcieDev->memIO[i].vaddr = ioremap_uc(pcieDev->memIO[i].start,
                pcieDev->memIO[i].len);
        if (!pcieDev->memIO[i].vaddr) {
            printk(KERN_DEBUG "pcieAdc: error in ioremap_uc [%d]. Aborting.\n", ret);
            return -ENOMEM;
        }
    }
    //virtual pointer to board registers
    pcieDev->pHregs = (PCIE_HREGS *) pcieDev->memIO[1].vaddr;

    return ret;
}

void setup_atca_parameters(PCIE_DEV *pcieDev) {
    STATUS_REG statusReg;
    statusReg.reg32 = ioread32((void*) & pcieDev->pHregs->status);
    firmwareRevision = statusReg.statFlds.revID;
    PDEBUG("%s setup, firmware: 0x%02X\n", DRV_NAME, firmwareRevision);
}

int reset_board(PCIE_DEV *pcieDev) {
    STATUS_REG statusReg;
    int i;

    statusReg.reg32 = ioread32((void*) & pcieDev->pHregs->status);
    statusReg.statFlds.RST = 1;
    iowrite32(statusReg.reg32, (void*) & pcieDev->pHregs->status);

    //wait for reset acknowledgment
    for (i = 0; i < WAIT_NOOP_CYCLES; i++) {
        udelay(10000);
        statusReg.reg32 = ioread32((void*) & pcieDev->pHregs->status);
        if (!(statusReg.statFlds.RST)){
            PDEBUG("%s reset at %d\n", DRV_NAME, i);
            break;
        }
    }
    PDEBUG("%s reset at %d, sReg: 0x%08X\n", DRV_NAME, i, statusReg.reg32);
    return 0;
}

//int setupDMA(PCIE_DEV *pcieDev, DMA_REG dmaReg, COMMAND_REG commandReg) {
int setup_dma(PCIE_DEV *pcieDev) {
    int i = 0;

    pcieDev->dmaIO.buf_size = DMA_NBYTES;

    // allocating DMA buffers
    for (i = 0; i < DMA_BUFFS; i++) {
        // set up a coherent mapping through PCI subsystem
        pcieDev->dmaIO.dmaBuffer[i].addr_v = pci_alloc_consistent(
                pcieDev->pdev, pcieDev->dmaIO.buf_size,
                &(pcieDev->dmaIO.dmaBuffer[i].addr_hw));
        if (!pcieDev->dmaIO.dmaBuffer[i].addr_v || !pcieDev->dmaIO.dmaBuffer[i].addr_hw) {
            printk(KERN_ERR  "pcieAdc: pci_alloc_consistent error (v:%p hw:%p). Aborting.\n",
                    (void*) pcieDev->dmaIO.dmaBuffer[i].addr_v,
                    (void*) pcieDev->dmaIO.dmaBuffer[i].addr_hw);
            return -ENOMEM;
        }
        memset((void*) (pcieDev->dmaIO.dmaBuffer[i].addr_v), 0,
                pcieDev->dmaIO.buf_size);
    }
     return 0;
}

int cleanup_dma(PCIE_DEV *pcieDev) {
    int i = 0;
    for (i = 0; i < DMA_BUFFS; i++) {
        //ClearPageReserved(virt_to_page(pcieDev->dmaIO.dmaBuffer[i].addr_v));
        pci_free_consistent(pcieDev->pdev, pcieDev->dmaIO.buf_size,
                pcieDev->dmaIO.dmaBuffer[i].addr_v,
                pcieDev->dmaIO.dmaBuffer[i].addr_hw);
    }

    // clear DMA addresses on board
    for (i = 0; i < DMA_BUFFS; i++) {
        iowrite32(0, (void*) & pcieDev->pHregs->HwDmaAddr[i]);
    }
    return 0;
}

//device open
int _open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "pci-atca-adc device driver access opened\n");
    return 0;
}

//device close
int _release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "pci-atca-adc device driver access closed(released)\n");
    return 0;
}
struct file_operations _fops = {
    .owner      = THIS_MODULE,
    // read =   _pcie_read,
    // write *   _pcie_write,
    .unlocked_ioctl  = pci_atca_adc_ioctl,
    .open       =  _open,
    .release    = _release
};

static unsigned char atca_adc_get_revision(struct pci_dev *dev)
{
    u8 revision;

    pci_read_config_byte(dev, PCI_REVISION_ID, &revision);
    return revision;
}

//****************************
//* DMA management functions *
//****************************

int enable_dma(struct pci_dev *pdev) {
    int ret;
    /*
       ret = pci_dma_supported(pdev, DMA_32BIT_MASK);
       if (!ret) {
       printk(KERN_ERR "pcieAdc: DMA not supported. Aborting.\n");
       return ret;
       }
       ret = pci_set_dma_mask(pdev, DMA_32BIT_MASK);
       if (ret) {
       printk(KERN_ERR "pcieAdc: pci_set_dma_mask error [%d]. Aborting.\n", ret);
       return ret;
       }
       ret = pci_set_consistent_dma_mask(pdev, DMA_32BIT_MASK);
       if (ret) {
       printk(KERN_ERR "pcieAdc: pci_set_consistent_dma_mask error [%d]. Aborting.\n",
       ret);
       return ret;
       }
       */
    if (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) {
        /* query for DMA transfer */
        /* @see Documentation/DMA-mapping.txt */
        PDEBUG("pci_set_dma_mask()\n");
        /* use 64-bit DMA */
        PDEBUG("Using a 64-bit DMA mask.\n");
        pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));

    } else if (!pci_set_dma_mask(pdev, DMA_BIT_MASK(32))) {
        PDEBUG("Could not set 64-bit DMA mask.\n");
        pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
        /* use 32-bit DMA */
        PDEBUG("Using a 32-bit DMA mask.\n");
    } else {
        printk(KERN_ERR "No suitable DMA possible.\n");
        return -EINVAL;
    }
    /* enable bus master capability */
    pci_set_master(pdev);
    // Enable Memory-Write-Invalidate transactions.
    ret = pci_set_mwi(pdev); // needed?
    if (ret) {
        printk(KERN_DEBUG "pcieAdc: pci_set_mwi error [%d]. Aborting.\n", ret);
        return ret;
    }
    return 0;
}

int disableDMAonboard(struct pci_dev *pdev) {
    pci_clear_mwi(pdev);

    return 0;
}

static int _probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
    int _ret = 0;
    PCIE_DEV *pcieDev = NULL;
    //COMMAND_REG commandReg;
   // DMA_REG dmaReg;

    //allocate the device instance block
    pcieDev = kzalloc(sizeof (PCIE_DEV), GFP_KERNEL);
    if (!pcieDev) {
        return -ENOMEM;
    }

    /* Do probing type stuff here.  
     * Like calling request_region();
     */
    if(pci_enable_device(pdev)) {
        dev_err(&pdev->dev, "can't enable PCI device\n");
        return -ENODEV;
    }

    if (atca_adc_get_revision(pdev) == 0x42)
        return -ENODEV;
    //    pcieDev->irq_lock = SPIN_LOCK_UNLOCKED;

    _ret = enable_dma(pdev);
    if (_ret != 0) {
        PDEBUG("pcieAdc: error in DMA initialization. Aborting.\n");
        return _ret;
    }

    pcieDev->pdev = pdev;
    pcieDev->wt_tmout = 20 * HZ;
    pci_set_drvdata(pdev, pcieDev);

    atca_configure_pci(pcieDev);
    // reset board
    reset_board(pcieDev);
    setup_atca_parameters(pcieDev);
    //Set up DMA
    _ret = setup_dma(pcieDev); //, dmaReg); commandReg);
    if (_ret) {
        //printk("pcieAdc: error in DMA setup. Aborting.\n");
        printk(KERN_ERR "%s setup_dma error[%d]\n", DRV_NAME, _ret);
        return _ret;
    }

    //init_MUTEX(&pcieDev->open_sem);
    sema_init(&pcieDev->open_sem, 1);
    //init spinlock
    spin_lock_init(&pcieDev->irq_lock);

    _ret = pci_enable_msi(pdev);
    if (_ret) {
        printk(KERN_ERR "pci_enable_msi %d error[%d]\n", pcieDev->pdev->irq, _ret);
        return _ret;
    }
    // Waitqueue initialization
    init_waitqueue_head(&pcieDev->rd_q);

    cdev_init(&pcieDev->cdev, &_fops);
    pcieDev->cdev.owner = THIS_MODULE;
    pcieDev->cdev.ops = &_fops;

    //_minor = sReg.statFlds.slotID;
    pcieDev->devno = MKDEV(device_major, current_board);
    _ret = cdev_add(&pcieDev->cdev, pcieDev->devno, 1);
    if (_ret ) {
        printk(KERN_ERR "Error %d adding _pcie device", _ret);
        return -EIO;
    }

    PDEBUG("board %s%d inserted.\n", DRV_NAME, current_board);
    pcieDev->dev = device_create(atca_ioc_class, NULL,
            pcieDev->devno, NULL, NODENAMEFMT, current_board);

    current_board++;
    return 0;
}

static void _remove(struct pci_dev *pdev)
{
    int i;
    /* clean up any allocated resources and stuff here.
     * like call release_region();
     */
    //get the device information data
    PCIE_DEV * pcieDev = (PCIE_DEV *) pci_get_drvdata(pdev);

    //#ifdef _MSI_ENABLE
    pci_disable_msi(pdev);
    //pci_disable_msi(pcieDev->pdev);
    //#endif
    //Reset
    reset_board(pcieDev);

    //deregistering DMAable areas
    cleanup_dma(pcieDev);

    device_destroy(atca_ioc_class, pcieDev->devno);

    //disable PCI board, deregister virtual addresses for the board
    for (i = 0; i < NUM_BARS; i++) {
        iounmap(pcieDev->memIO[i].vaddr);
    }

    kfree(pcieDev);
    pci_set_drvdata(pdev, NULL);
    current_board--;
    printk(KERN_INFO "board %s%d removed.\n", DRV_NAME, current_board);
}

static struct pci_driver pci_driver = {
    .name = "pci_atca_adc",
    .id_table = ids,
    .probe = _probe,
    .remove = _remove,
};

static int __init pci_atca_adc_init(void)
{
    int _ret;

    dev_t _devno = 0;
    _devno = MKDEV(0, 0);

    _ret = alloc_chrdev_region(&_devno, 0, MAX_DEVICES, DRV_NAME);
    if (_ret) {
        printk(KERN_ERR "Failed to register device %s with error %d\n", DRV_NAME, _ret);
        goto fail;
    }
    device_major = MAJOR(_devno);
    //PDEBUG("pci_atca_adc_iINOR_NUMBERSnit: device_num:%d\n", device_major);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    atca_ioc_class = class_create(DRV_NAME);
#else
    atca_ioc_class = class_create(THIS_MODULE, DRV_NAME);
#endif
    if (IS_ERR(atca_ioc_class)) {
        printk(KERN_ERR "Unable to allocate class\n");
        _ret = PTR_ERR(atca_ioc_class);

        goto unreg_chrdev;
    }

    _ret = pci_register_driver(&pci_driver);
    if (_ret) {
        printk(KERN_ERR "pci_atca_adc_init error(%d).\n", _ret);
        goto unreg_class;
    }
    PDEBUGG("%s: Init.\n", DRV_NAME);
    return 0;
unreg_class:
    //class_unregister(atca_ioc_class);
    class_destroy(atca_ioc_class);
unreg_chrdev:
    unregister_chrdev_region(MKDEV(device_major,0), MAX_DEVICES);
fail:
    return _ret;
}

static void __exit pci_atca_adc_exit(void)
{
    pci_unregister_driver(&pci_driver);
    //class_unregister(atca_ioc_class);
    class_destroy(atca_ioc_class);
}

//MODULE_LICENSE("GPL");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Module for PCIe ATCA-IOC FPGA ");
MODULE_AUTHOR("Bernardo Carvalho/IST-IPFN");

module_init(pci_atca_adc_init);
module_exit(pci_atca_adc_exit);

//  vim: syntax=c ts=4 sw=4 sts=4 sr et
