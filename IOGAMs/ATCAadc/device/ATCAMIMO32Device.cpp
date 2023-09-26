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
#include <string.h>
//#include <string>
//#include <cstring>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <errno.h>
//#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>  // For mmap()

#include "ATCAMIMO32Device.h"
#include "pci-atca-adc-ioctl.h"

namespace atca {
    ATCAMIMO32Device::ATCAMIMO32Device(uint32_t bufferSize): //, bool useRTReadThread) :
        deviceHandle(0), mapBase(NULL),
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
        //deviceHandle = ::open(deviceName, O_RDONLY);
        deviceHandle = ::open(deviceName, O_RDWR);
#endif
        if (deviceHandle == -1)
            return -1;

        //::mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, deviceHandle, 0);
        //void *mmap(void *addr, size_t length, int prot, int flags,
//                  int fd, off_t offset);

        mapBase = ::mmap(0, MAP_SIZE, PROT_READ, MAP_SHARED, deviceHandle, 0);

         char errBuf[ 256 ];
        if (mapBase == MAP_FAILED)
        {
            //::close(deviceHandle);
            std::cerr << "MMAP Failed " << mapBase << ", errno: " << 
                strerror_r(errno, errBuf, 256) << std::endl;
            //std::cerr << "MMAP Failed, closing device" << mapBase << std::endl;
            //deviceHandle = -1;
#ifdef DEBUG
            //fprintf(stderr, "Error Mapping Device name = %s\n", devname);
#endif
            //return EXIT_FAILURE; //MAP_FAILED;
        }
        isDeviceOpen = true;
        return 0;
    }

    int ATCAMIMO32Device::close()
    {
        int result = 0;
        if(!isDeviceOpen) {
            return EXIT_FAILURE;
        }

        //::munmap(mapBase, MAP_SIZE);
        errno = 0;
#ifndef DUMMYMODE
        /*close() returns zero on success.  On error, -1 is returned, and errno is set appropriately.*/
        result = ::close(deviceHandle);
#endif

        if (result)
            return errno;

        deviceHandle = -1;
        isDeviceOpen = false;
        return result;

    }

    size_t ATCAMIMO32Device::read(void *buf, size_t count)
    {
        if(!isDeviceOpen) {
            return EBADF;
        }
        size_t result  = ::read(deviceHandle, buf, count);
        return result;
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
/*
        int buffInt[2];
        int rc = ::read(deviceHandle, buffInt, 4);
        if(rc<0) std::cerr << "read() Failed, " << rc << std::endl;
        buffInt[0] = 1;
        rc = ::write(deviceHandle, buffInt, 4);
        if(rc<0) std::cerr << "write() Failed, " << rc << std::endl;
//#endif
*/
        return result;
    }

} // namespace atca

//  vim: syntax=cpp ts=4 sw=4 sts=4 sr et
