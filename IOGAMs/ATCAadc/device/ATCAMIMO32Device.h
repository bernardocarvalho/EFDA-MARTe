/* ----------------------------------------------------------------------------
 * file: ATCAMIMO32Device.h
 * project: atca-mimo32
 * by: Torsten Bluhm
 *
 * Copyright (c) 2015, All rights reserved.
 * Max-Planck-Institut für Plasmaphysik. W7-X CoDaC group.
 * ----------------------------------------------------------------------------
 */

#ifndef ATCAMIMO32DEVICE_H_
#define ATCAMIMO32DEVICE_H_

#define DMA_SIZE (4194304/8)
#define NUM_CHAN 32

//#define DUMMYMODE
//#define DEBUG

#ifdef DEBUG
#include <time.h>
#endif

#include <stdint.h>
#include <string>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

namespace atca
{

    class ATCAMIMO32Device
    {

        public:
            ATCAMIMO32Device(uint32_t bufferSize);//, bool useRTReadThread = false);
            virtual ~ATCAMIMO32Device();
            int open(string deviceName);
            int close();
            int setup(bool softTrigger, uint32_t readTimeout, bool chopped,
                    uint16_t chopperFreq = 1000);
            string getDeviceName()

            {
                return deviceName;
            }
            /*
               int getBufferFillSize()
               {
               return dmaBufferFillSize;
               }
               */
            //int getSampleCounter(uint16_t* counter);
            int getStatus(uint16_t* status);
            int enableAcquisition();
            int disableAcquisition();
            int read(int16_t* buffer, uint8_t nChannels, uint32_t nSamples);

        private:
            string deviceName;
            int deviceHandle;
            //bool useRTReadThread;
            bool softTrigger;
            uint8_t* dmaBuffer;
            uint64_t dmaBufferSize;
            //  uint64_t dmaBufferOffset;
            // uint64_t dmaBufferFillSize;
            pthread_t dmaReadThread;
            bool dmaReadLoopActive;
            sem_t readSemaphore;
            pthread_mutex_t readMutex;

#ifdef DEBUG
            uint64_t counter;
            struct timespec readTime;
            FILE* readTimesFile;
#endif

            // int disableChopper();
            // int enableChopper(uint16_t chopperFreq);
            int createDMAReadThread();
            static void* dmaReadLoop(void* device);

    };

} // namespace atca

#endif // ATCAMIMO32DEVICE_H_

//  vim: syntax=cpp ts=4 sw=4 sts=4 sr et
