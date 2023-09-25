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
//#include <unistd.h>
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
    uint32_t statusReg;

    int runTest(int argc, char* argv[]) {

        char devname[64];
        ATCAMIMO32Device device(1024*8); //, dataMbSize, dmaBufferSize);
        snprintf(devname, 64, ATCA_NODE_NAME_FMT, deviceNumber);
#ifdef DEBUG
        printf("Opening Device name = %s,\t", devname);
#endif
        int rc = device.open(devname);
        //deviceHandle = ::open(devname, O_RDWR | O_SYNC);
        if (deviceHandle == -1){
            return EXIT_FAILURE;
        }
        //::close(deviceHandle);
        //device.disableAcquisition();
        device.readStatus(&statusReg);
        std::cout << "Device statusReg: "<< statusReg << std::endl;
        device.close();
        //::close(deviceHandle);
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

