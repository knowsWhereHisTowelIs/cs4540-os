#include <stdint.h>

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
        char startingPriority;
        // Current priority of the process which may change with aging.
        char currentPriority;
        //Time in CPU needed before/between I/O (set once)
        int ioInBetweenTime;
        //Time I/O takes (set once)
        int ioDuration;
        //Total time in machine not counting time in wait queue (set at startup counts down).  How much time process spends doing something before it exits.  Sum of total time in CPU and total time in I/O.
        int totalTimeInMachine;
        //Time in CPU currently.  Set to 0 when moved into CPU, when reaches A or quantum is up moves out of CPU.
        int timeInCpu;
        //Time left waiting for current I/O
        int timeLeftInBlocked;
        //Time process has been waiting in ready queue
        int timeInReadyQueue;
        //Total time in CPU
        int totalTimeInCpu;
        //Total time in I/O
        int totalTimeInIo;
        //Total time in ready queue
        int totalTimeInReadyQueue;
        //Smallest time in ready queue
        int smallestTimeInQueue;
        //Longest time in ready queue
        int longestTimeInReadyQueue;
        //  You need to keep track of the current state of each process; you might have a field in each process or use which data structure it is in.  In CPU, I/O wait, Ready queue ….
        int state;
        // Name of process
        char** name;
    } process_t;

    // ======================== PROTOTYPES =====================================
    void populateProcess(
        process_t *process, char *name, char startingPriority,
        int ioInBetweenTime, int ioDuration
    );
#endif
