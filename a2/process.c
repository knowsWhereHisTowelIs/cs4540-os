#include "process.h"

char hasProcesses() {
    return 1;
}

void populateProcess(
            process_t *process, char *name, char startingPriority,
            char currentPriority, int ioInBetweenTime, int ioDuration
        ) {
    process->startingPriority = startingPriority;
    process->currentPriority = currentPriority;
    process->ioInBetweenTime = ioInBetweenTime;
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
    process->state = 0;
    *process->name = name;
}
