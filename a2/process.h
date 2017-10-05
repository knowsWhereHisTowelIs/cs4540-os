#include <stdint.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <errno.h>

#ifndef PROCESS_H
    #define PROCESS_H
    // ======================== DEFINITIONS ====================================
    #define PROCESS_STATE__SUSPENDED 0
    #define PROCESS_STATE__CPU 1
    #define PROCESS_STATE__IOWAIT 2
    #define PROCESS_STATE__BLOCKED 3
    #define PROCESS_STATE__COMPLETED -1

    // ======================== TYPEDEFS =======================================
    typedef struct {
        // Starting priority, reset current priority to this each time process moved into wait queue, does not change.
        uint8_t startingPriority;
        // Current priority of the process which may change with aging.
        uint8_t currentPriority;

        // time to start the process in the loop
        uint32_t startTime;
        // the time until the process completes
        uint32_t runTime;

        //Time in CPU needed before/between I/O (set once)
        uint32_t ioTriggeredInterval;
        //Time I/O takes (set once)
        uint32_t ioDuration;
        //Total time in machine not counting time in wait queue (set at startup counts down).  How much time process spends doing something before it exits.  Sum of total time in CPU and total time in I/O.
        uint32_t totalTimeInMachine;
        //Time in CPU currently.  Set to 0 when moved into CPU, when reaches A or quantum is up moves out of CPU.
        uint32_t timeInCpu;
        //Time left waiting for current I/O
        uint32_t timeLeftInBlocked;
        //Time process has been waiting in ready queue
        uint32_t timeInReadyQueue;
        //Total time in CPU
        uint32_t totalTimeInCpu;
        //Total time in I/O
        uint32_t totalTimeInIo;
        //Total time in ready queue
        uint32_t totalTimeInReadyQueue;
        //Smallest time in ready queue
        uint32_t smallestTimeInQueue;
        //Longest time in ready queue
        uint32_t longestTimeInReadyQueue;
        //  You need to keep track of the current state of each process; you might have a field in each process or use which data structure it is in.  In CPU, I/O wait, Ready queue ….
        char state;
        // Name of process
        char* name;
    } process_t;

    // ======================== PROTOTYPES =====================================
    void populateProcess(
                process_t *process, char *name, char startingPriority,
                uint32_t ioTriggeredInterval, uint32_t ioDuration, int startTime, int runTime
            );
#endif
