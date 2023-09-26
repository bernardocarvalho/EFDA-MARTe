/* ----------------------------------------------------------------------------
 * file: ATCAMIMO32Device.cpp
 * project: atca-mimo32
 * by: Torsten Bluhm
 *
 * Copyright (c) 2015, All rights reserved.
 * Max-Planck-Institut für Plasmaphysik. W7-X CoDaC group.
 * ----------------------------------------------------------------------------
 */

#include <fcntl.h>
#include <unistd.h>
//#include <string>
//#include <cstring>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <errno.h>
//#include <sys/types.h>
#include <sys/ioctl.h>

#include "ATCAMIMO32Device.h"
#include "pci-atca-adc-ioctl.h"

namespace atca {
    ATCAMIMO32Device::ATCAMIMO32Device(uint32_t bufferSize): //, bool useRTReadThread) :
        isDeviceOpen(false), dmaReadThread(0), dmaReadLoopActive(false)
    {
        dmaBufferSize = bufferSize ;// * 1024LL * 1024LL;

        dmaBuffer = (uint8_t*) malloc(dmaBufferSize);
        if (dmaBuffer == NULL)
            fprintf(stderr, "Failed to allocate memory (%llu bytes)\n",
                    dmaBufferSize);
        sem_init(&readSemaphore, 0, 10);
        pthread_mutex_init(&readMutex, NULL);

#ifdef DEBUG
        readTimesFile = NULL;
#endif
    }

    ATCAMIMO32Device::~ATCAMIMO32Device()
    {
        free(dmaBuffer);
        sem_destroy(&readSemaphore);
        pthread_mutex_destroy(&readMutex);
    }

    int ATCAMIMO32Device::open(char *deviceName)
    {
        if(isDeviceOpen) {
            std::cerr << "Device already opened, closing device." << std::endl;
            close();
        }
        //this->deviceName = deviceName;
        errno = 0;
#ifdef DUMMYMODE
        deviceHandle = 0;
#else
        deviceHandle = ::open(deviceName, O_RDONLY);
#endif
        if (deviceHandle == -1)
            return -1;
        isDeviceOpen = true;
        return 0;
    }

    int ATCAMIMO32Device::close()
    {
        int result = 0;
        if(!isDeviceOpen) {
            return EXIT_FAILURE;
        }
        isDeviceOpen = false;

        errno = 0;
#ifndef DUMMYMODE
        result = ::close(deviceHandle);
#endif

        //if (result == 0)
        deviceHandle = -1;

        return errno;
    }

    int ATCAMIMO32Device::readStatus(uint32_t* statusp)
    {
        if(!isDeviceOpen) {
            return EXIT_FAILURE;
        }
        int result = ::ioctl(deviceHandle, PCIE_ATCA_ADC_IOCG_STATUS_REG, statusp);
        return result;
    }

    int ATCAMIMO32Device::enableAcquisition()
    {
        if(!isDeviceOpen) {
            return EXIT_FAILURE;
        }
        int result = ::ioctl(deviceHandle, PCIE_ATCA_ADC_IOCT_ACQ_ENABLE);
        return result;
    }
    int ATCAMIMO32Device::disableAcquisition()
    {
        if(!isDeviceOpen) {
            return EXIT_FAILURE;
        }
//#ifndef DUMMYMODE
        int result = ::ioctl(deviceHandle, PCIE_ATCA_ADC_IOCT_ACQ_DISABLE);
//#endif
        return result;
    }

} // namespace atca

//  vim: syntax=cpp ts=4 sw=4 sts=4 sr et
