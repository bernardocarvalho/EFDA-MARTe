/*
 * Copyright 2011 EFDA | European Fusion Development Agreement
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they 
 will be approved by the European Commission - subsequent  
 versions of the EUPL (the "Licence"); 
 * You may not use this work except in compliance with the 
 Licence. 
 * You may obtain a copy of the Licence at: 
 *  
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in 
 writing, software distributed under the Licence is 
 distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
 express or implied. 
 * See the Licence for the specific language governing 
 permissions and limitations under the Licence. 
 *
 * $Id: pcieAdcIoctl.h 26 2012-01-31 08:52:21Z aneto $
 *
 **/
#ifndef _PCIE_ATCA_ADC_IOCTL_H_
#define _PCIE_ATCA_ADC_IOCTL_H_

/*
 * IOCTL definitions
 */
#define PCIE_ATCA_ADC_IOC_MAGIC 'l'  // /* Please use a different 8-bit number in your code */
/*See  /Documentation/ioctl-number.txt*/

/*
 * S means "Set" through a ptr,
 * T means "Tell" directly
 * G means "Get" (to a pointed var)
 * Q means "Query", response is on the return value
 * X means "eXchange": G and S atomically
 * H means "sHift": T and Q atomically
 */


#define PCIE_ATCA_ADC_IOCT_ACQ_ENABLE           _IO(PCIE_ATCA_ADC_IOC_MAGIC,  1)
#define PCIE_ATCA_ADC_IOCT_ACQ_DISABLE          _IO(PCIE_ATCA_ADC_IOC_MAGIC,  2)
#define PCIE_ATCA_ADC_IOCG_NUM_BOARDS           _IOR(PCIE_ATCA_ADC_IOC_MAGIC, 3, u_int32_t)
#define PCIE_ATCA_ADC_IOCG_MASTER_SLOT_NUM      _IOR(PCIE_ATCA_ADC_IOC_MAGIC, 4, u_int32_t)
#define PCIE_ATCA_ADC_IOCS_SET_EXT_CLK_TRG      _IOW(PCIE_ATCA_ADC_IOC_MAGIC, 5, u_int32_t)
#define PCIE_ATCA_ADC_IOCT_IS_RTM_PRESENT       _IOWR(PCIE_ATCA_ADC_IOC_MAGIC, 6, u_int32_t)
#define PCIE_ATCA_ADC_IOCT_SOFT_TRG             _IO(PCIE_ATCA_ADC_IOC_MAGIC,  7)
#define PCIE_ATCA_ADC_IOCG_GET_BOARD_SLOT_NS    _IOR(PCIE_ATCA_ADC_IOC_MAGIC, 8, u_int32_t)
#define PCIE_ATCA_ADC_IOCT_ACQ_DEBUG            _IO(PCIE_ATCA_ADC_IOC_MAGIC,  9)
#define PCIE_ATCA_ADC_IOCS_N_IN_ANA_CHANNELS    _IOWR(PCIE_ATCA_ADC_IOC_MAGIC, 10, u_int32_t)
#define PCIE_ATCA_ADC_IOCS_N_IN_DIG_CHANNELS    _IOWR(PCIE_ATCA_ADC_IOC_MAGIC, 11, u_int32_t)
#define PCIE_ATCA_ADC_IOCS_N_OUT_ANA_CHANNELS   _IOWR(PCIE_ATCA_ADC_IOC_MAGIC, 12, u_int32_t)
#define PCIE_ATCA_ADC_IOCS_N_OUT_DIG_CHANNELS   _IOWR(PCIE_ATCA_ADC_IOC_MAGIC, 13, u_int32_t)
#define PCIE_ATCA_ADC_IOCG_STATUS_REG           _IOR(PCIE_ATCA_ADC_IOC_MAGIC, 14, u_int32_t)

#define PCIE_ATCA_ADC_IOC_MAXNR                 14

#endif /* _PCIE_ATCA_ADC_IOCTL_H_ */

//  vim: syntax=cpp ts=4 sw=4 sts=4 sr et
