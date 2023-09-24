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
#include <linux/uaccess.h>
#include "pci-atca-adc-ioctl.h"

//ssize_t pci-atca-adc-ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg){
long pci_atca_adc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    int err       = 0;
    u32 tempValue = 0;

    //extract the type and number bitfields, and don't decode
    //wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
    if (_IOC_TYPE(cmd) != PCIE_ATCA_ADC_IOCT_MAGIC)
        return -ENOTTY;
    if (_IOC_NR(cmd) > PCIE_ATCA_ADC_IOCT_MAXNR)
        return -ENOTTY;

    /*
     * the type is a bitmask, and VERIFY_WRITE catches R/W
     * transfers. Note that the type is user-oriented, while
     * verify_area is kernel-oriented, so the concept of "read" and
     * "write" is reversed
     */
    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err =  !access_ok((void __user *)arg, _IOC_SIZE(cmd));
    if (err)
        return -EFAULT;

    switch(cmd) {
        case PCIE_ATCA_ADC_IOCT_ACQ_ENABLE:
            //EnableATCApcieAcquisition();
            break;
        case PCIE_ATCA_ADC_IOCT_ACQ_DISABLE:
            //DisableATCApcieAcquisition();
            break;
            /*
               case PCIE_ATCA_ADC_IOCT_NUM_BOARDS:
               tempValue = GetNumberOfBoards();
               if(copy_to_user((void __user *)arg, &tempValue, sizeof(u32)))
               return -EFAULT;
               break;
               case PCIE_ATCA_ADC_IOCT_MASTER_SLOT_NUM:
               tempValue = GetMasterBoardSlotNumber();
               if(copy_to_user((void __user *)arg, &tempValue, sizeof(u32))){
               return -EFAULT;
               }
               break;
               case PCIE_ATCA_ADC_IOCT_SET_EXT_CLK_TRG:
               tempValue = 0;
               if(copy_from_user(&tempValue, (void __user *)arg, sizeof(u32))){
               return -EFAULT;
               }
               if(tempValue < 0 || tempValue > 1){
               return -EFAULT;
               }
               SetATCApcieExternalTriggerAndClock(tempValue);
               break;
               case PCIE_ATCA_ADC_IOCT_IS_RTM_PRESENT:
               tempValue = 0;
               if(copy_from_user(&tempValue, (void __user *)arg, sizeof(u32))){
               return -EFAULT;
               }
               tempValue = IsRTMPresent(tempValue);
               if(copy_to_user((void __user *)arg, &tempValue, sizeof(u32))){
               return -EFAULT;
               }
               break;
               case PCIE_ATCA_ADC_IOCT_N_IN_ANA_CHANNELS:
               tempValue = 0;
               if(copy_from_user(&tempValue, (void __user *)arg, sizeof(u32))){
               return -EFAULT;
               }
               tempValue = GetNumberOfInputAnalogChannels(tempValue);
               if(copy_to_user((void __user *)arg, &tempValue, sizeof(u32))){
               return -EFAULT;
               }
               break;
               case PCIE_ATCA_ADC_IOCT_N_IN_DIG_CHANNELS:
               tempValue = 0;
               if(copy_from_user(&tempValue, (void __user *)arg, sizeof(u32))){
               return -EFAULT;
               }
               tempValue = GetNumberOfInputDigitalChannels(tempValue);
               if(copy_to_user((void __user *)arg, &tempValue, sizeof(u32))){
               return -EFAULT;
               }               
               break;
               case PCIE_ATCA_ADC_IOCT_N_OUT_ANA_CHANNELS:
               tempValue = 0;
               if(copy_from_user(&tempValue, (void __user *)arg, sizeof(u32))){
               return -EFAULT;
               }
               tempValue = GetNumberOfAnalogueOutputChannels(tempValue);
               if(copy_to_user((void __user *)arg, &tempValue, sizeof(u32))){
               return -EFAULT;
               }
               break;
               case PCIE_ATCA_ADC_IOCT_N_OUT_DIG_CHANNELS:
               tempValue = 0;
               if(copy_from_user(&tempValue, (void __user *)arg, sizeof(u32))){
               return -EFAULT;
               }
               tempValue = GetNumberOfDigitalOutputChannels(tempValue);
               if(copy_to_user((void __user *)arg, &tempValue, sizeof(u32))){
               return -EFAULT;
               }
            break;
        case PCIE_ATCA_ADC_IOCT_SEND_SOFT_TRG:
            SendSoftwareTrigger();
            break;
        case PCIE_ATCA_ADC_IOCT_GET_BOARD_SLOT_NS:
            if(access_ok(VERIFY_WRITE, (void __user *)arg, GetNumberOfBoards() * sizeof(u32))){
                if(copy_to_user((void __user *)arg, board_slot_numbers, GetNumberOfBoards() * sizeof(u32))){
                    return -EFAULT;
                }
            }
            else{
                printk("Bad memory provided to copy ");
                return -EFAULT;
            }
            break;
        case PCIE_ATCA_ADC_IOCT_ACQ_DEBUG:
            printk("DMA_global_addr[0] = %d\n", *((u32 *)DMA_global_addr[0]));
            printk("DMA_global_addr[1] = %d\n", *((u32 *)DMA_global_addr[1]));
            printk("DMA_global_addr[2] = %d\n", *((u32 *)DMA_global_addr[2]));
            printk("DMA_global_addr[3] = %d\n", *((u32 *)DMA_global_addr[3]));
            break;
            */
        default:  /* redundant, as cmd was checked against MAXNR */
                return -ENOTTY;

    }
    return 0;
}

//  vim: syntax=cpp ts=4 sw=4 sts=4 sr et
