/*
 * atca-mimo32-v2-test.cpp
 *
 * Copyright (c) 2020-present,  IPFN-IST / IPP-MPG
 * All rights reserved.
 *
 * This source code is licensed under BSD-style license (found in the
 * LICENSE file in the root directory of this source tree)
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define ATCA_NODE_NAME_FMT  "/dev/atca_ioc_%d"

namespace atca_test
{
    //    int numberOfAcquisitionRounds = 0;
    int deviceNumber = 0;
    int deviceHandle;


    int runTest(int argc, char* argv[]) {

        char devname[64];
        snprintf(devname, 64, ATCA_NODE_NAME_FMT, deviceNumber);
#ifdef DEBUG
        printf("Opening Device name = %s,\t", devname);
#endif
        deviceHandle = ::open(devname, O_RDWR | O_SYNC);
        if (deviceHandle == -1){
            return EXIT_FAILURE;
        }
        ::close(deviceHandle);
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

