#include "process.h"

void populateProcess(
            process_t *process, char *name, char startingPriority,
            uint32_t ioTriggeredInterval, uint32_t ioDuration, int startTime, int runTime
        ) {
    process->startingPriority = startingPriority;
    process->currentPriority = startingPriority;
    process->startTime = startTime;
    process->runTime = runTime;
    process->ioTriggeredInterval = ioTriggeredInterval;
    process->ioDuration = ioDuration;
    process->totalTimeInMachine = 0;
    process->timeInCpu = 0;
    process->timeLeftInBlocked = 0;
    process->timeInReadyQueue = 0;
    process->timeInReadyQueue = 0;
    process->totalTimeInIo = 0;
    process->totalTimeInReadyQueue = 0;
    process->smallestTimeInQueue = 0;
    process->longestTimeInReadyQueue = 0;
    process->state = PROCESS_STATE__SUSPENDED;
    process->name = name;
}
