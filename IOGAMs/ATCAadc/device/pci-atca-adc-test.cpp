/*
 * atca-mimo32-v2-test.cpp
 *
 * Copyright (c) 2020-present,  IPFN-IST / IPP-MPG
 * All rights reserved.
 *
 * This source code is licensed under BSD-style license (found in the
 * LICENSE file in the root directory of this source tree)
 */
//#include <stdio.h>
#include <unistd.h>
//#include <fcntl.h>
//#include <stdlib.h>
#include <iostream>
//#include <sys/types.h>
//#include <sys/stat.h>

#include "ATCAMIMO32Device.h"

#define ATCA_NODE_NAME_FMT  "/dev/atca_ioc_%d"

using namespace atca;

namespace atca_test
{
    //    int numberOfAcquisitionRounds = 0;
    int deviceNumber = 0;
    int deviceHandle;
    uint32_t statusReg, hwcounterReg;

    int runTest(int argc, char* argv[]) {

        char devname[64];
        int rc;

        ATCAMIMO32Device device(1024*8); //, dataMbSize, dmaBufferSize);
        snprintf(devname, 64, ATCA_NODE_NAME_FMT, deviceNumber);
        //#ifdef DEBUG
        //#endif
        //int rc = device.open(devname);
        if(device.open(devname)) {
            std::cerr << "Failed Opening Device name = " << devname << std::endl;
            return EXIT_FAILURE;
        }
        else
            std::cout << "Openned Device name = " << devname << std::endl;
        
        if(rc = device.enableAcquisition())
            std::cerr << "Device EN ACQ ioctl Error: "<< rc << std::endl;
        device.readHwCounter(&hwcounterReg);
        std::cout << "Device hwcounterReg: "<< hwcounterReg << std::endl;
        usleep(1000);
        device.readHwCounter(&hwcounterReg);
        std::cout << "Device hwcounterReg: "<< hwcounterReg << std::endl;

        if(rc = device.disableAcquisition())
            std::cerr << "Device DIS ACQ ioctl  Error: "<< rc << std::endl;

        if(device.readStatus(&statusReg))
            std::cerr << "Device statusReg read Error: "<< std::endl;
        else
            std::cout << "Device statusReg: 0x"<< std::hex << statusReg << std::endl;
            //printf("Device statusReg: 0x%08X.\n", statusReg);
        device.close();
        return EXIT_SUCCESS;
    }
} // namespace atca_test

int main(int argc, char* argv[])
{
    return atca_test::runTest(argc, argv);
}

/*
 * vim: syntax=cpp ts=4 sw=4 sts=4 sr et
 */

