/**
 * ATCA IO CONTROL Integrator
 * Project Name:   ATCA DAQ
 * Design Name:    ATCA-MIMO-DAQ Streaming  Linux Device Driver
 * PCI Device Id: 24
 * FW Version AA
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
#include <linux/cdev.h>
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
#define CHAR_DEVICE_NAME            "pcieATCAAdc"
static int master_board_index = -1;
static int DMA_NBYTES         = 0;
// Global DMA address
int DMA_global_addr[MAX_BOARDS * DMA_BUFFS];

// DAC locations
int DAC_addr[MAX_BOARDS * N_DACS_PER_BOARDS];

// DIO locations
int DIO_addr[MAX_BOARDS * N_DIOS_PER_BOARD];

// Command register locations (in order to export the enable and disable acquisition function)
int command_register_addr[MAX_BOARDS];

// Status register locations
int status_register_addr[MAX_BOARDS];

// The slot numbers for each of the board indexes
int board_slot_numbers[MAX_BOARDS];

static int SlotNumberToBoardIndex(int slotNum) {
    int i = 0;
    for (i = 0; i < MAX_BOARDS; i++) {
        if (board_slot_numbers[i] == slotNum) {
            return i;
        }
#define CHAR_DEVICE_NAME            "pcieATCAAdc"
    }
    return -1;
}

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
    printk(KERN_DEBUG "%s%d inserted.\n", DRV_NAME, current_board);
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

//struct file_operations _fops;
/*   Function prototypes          */

/*
 * The ioctl() implementation
 */

long _ioctl (struct file *filp, unsigned int cmd, unsigned long arg){
    return 0;

}

//device open
//ssize_t _open(struct inode *inode, struct file *file) {
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
    .unlocked_ioctl  = _ioctl,
    .open       =  _open,
    .release    = _release
};

static unsigned char atca_adc_get_revision(struct pci_dev *dev)
{
    u8 revision;

    pci_read_config_byte(dev, PCI_REVISION_ID, &revision);
    return revision;
}

static int _probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
    int _ret = 0;
    PCIE_DEV *pcieDev = NULL;
    COMMAND_REG commandReg;
    DMA_REG dmaReg;


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

    // reset board
    //resetBoard(pcieDev);

    pcieDev->pdev = pdev;
    pcieDev->wt_tmout = 20 * HZ;
    pci_set_drvdata(pdev, pcieDev);

    atca_configure_pci(pcieDev);
    //init_MUTEX(&pcieDev->open_sem);
    sema_init(&pcieDev->open_sem, 1);
    //init spinlock
    spin_lock_init(&pcieDev->irq_lock);

    //#ifdef _MSI_ENABLE    
    _ret = pci_enable_msi(pdev);
    if (_ret) {
        printk(KERN_ERR "pci_enable_msi %d error[%d]\n", pcieDev->pdev->irq, _ret);
        return _ret;
    }
    //#endif
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

    //printk(KERN_INFO "current_board is = %d\n", current_board);
    printk(KERN_DEBUG "board %s%d inserted.\n", DRV_NAME, current_board);
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
    // resetBoard(pcieDev);

    //deregistering DMAable areas
    //cleanupDMA(pcieDev);

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
    printk(KERN_DEBUG "pcieAdc: Init.\n");
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

//  vim: syntax=cpp ts=4 sw=4 sts=4 sr et
