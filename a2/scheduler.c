/**
 * @author: Caleb Slater
 * @class: ECE 4540
 * @assignment: 2
**/
#include "scheduler.h"

void initialize(schedulingInfo_t *schedulingInfo) {
    int i;
    schedulingInfo->quantums.current = 0;
    schedulingInfo->quantums.lastSwap = 0;
    schedulingInfo->quantums.lastAge = 0;

    schedulingInfo->created = 0;
    // array of processes based on priority 0-15
    schedulingInfo->processes.list = (arrayList_t**) malloc(sizeof(arrayList_t*) * PRIORITY_LEVELS);
    for(i = 0; i < PRIORITY_LEVELS; i++) {
        schedulingInfo->processes.list[i] = arraylist_create();
    }
    // initialize array of process list
    schedulingInfo->processes.completedList = arraylist_create();
    schedulingInfo->processes.waitingForIoList = arraylist_create();
    schedulingInfo->processes.toRun = arraylist_create();
}

void createTestProcessList(schedulingInfo_t *schedulingInfo) {
    int priority, i;
    uint32_t startTime, runTime, ioTriggeredInterval, ioDuration;
    char *name;

    startTime = 0;
    runTime = 2048;

    for(priority = 0; priority < PRIORITY_LEVELS; priority++ ) {
        for(i = 0; i < 4; i++) {
            process_t *process = (process_t*) malloc(sizeof(process_t));
            // allocate 32 bytes for the string and populate with null
            name = (char*) calloc(sizeof(char), 32);
            sprintf(name, "Process No. is %d", schedulingInfo->created);

            populateProcess(process, name, priority, ioTriggeredInterval, ioDuration, startTime, runTime);
            arraylist_add(schedulingInfo->processes.toRun, process);
            schedulingInfo->created++;

            // random int from 1 to 100
            ioTriggeredInterval = (priority * 100) + (i * 10) + 1;
            ioDuration = (priority * 100) + (i * 10) + 1;
            startTime += 10;
            // startTime += (rand() % 25);
            // runTime = (rand() % 1024) + 1;

            printf("\n==========Created process with priority:%d and number:%d==========\n", priority, i);
            printProcessInfo(process);
        }
    }
}

char hasProcesses(schedulingInfo_t *schedulingInfo) {
    return (arraylist_getsize(schedulingInfo->processes.toRun) > 0) ? 1 : 0;
}

void queueProcesses(schedulingInfo_t *schedulingInfo) {
    int i;
    int listSize = arraylist_getsize(schedulingInfo->processes.toRun);
    // TODO remove
    fprintf(stderr, "listSize:%d\n", listSize);
    // for( i = 0; i < listSize && i < 8; i++) {
    //     process_t *process = (process_t*) arraylist_get(schedulingInfo->processes.toRun, i);
    //     int p = process != NULL ? process->startingPriority : -1;
    //     fprintf(stderr, "%02d  [%02d]\t:\t%d\n", process->currentPriority, i%4, process);
    // }
    for( i = 0; i < listSize; i++) {
        process_t *process = (process_t*) arraylist_get(schedulingInfo->processes.toRun, 0);

        // TODO remove
        fprintf(stderr, "\nBEFORE if %d qc %d \n", i, schedulingInfo->quantums.current);
        fprintf(stderr, "process is null = 0? %d %ld \n", process == NULL ? 0 : 1, process);
        fprintf(stderr, "BEFORE st %d \n", process->startTime);

        if( schedulingInfo->quantums.current >= process->startTime ) {
            // TODO remove
            fprintf(stderr, "Queueing process[%s] because %u > %u b4 add\n", process->name, schedulingInfo->quantums.current, process->startTime);
            arraylist_add(schedulingInfo->processes.list[ process->startingPriority ], process);
            fprintf(stderr, "BEFORE REMOVE\n");
            arraylist_remove(schedulingInfo->processes.toRun, 0, 1);
            fprintf(stderr, "AFTER REMOVE\n");
        }
    }
    fprintf(stderr, "HERE\n");
}

char getAction(schedulingInfo_t *schedulingInfo) {
    char action;
    uint32_t quantumsSinceSwap = schedulingInfo->quantums.current - schedulingInfo->quantums.lastSwap;

    if( schedulingInfo->processes.active == NULL ) {
        action = ACTION__SWAP;
    } else if ( quantumsSinceSwap < TIME_QUANTUM ) {
        if( schedulingInfo->processes.active->ptr->state == PROCESS_STATE__CPU ) {
            action = ACTION__EXECUTE;
        } else {
            action = ACTION__BLOCK;
        }
    } else {
        action = ACTION__SWAP;
    }
    return action;
}

void ageProcesses(schedulingInfo_t *schedulingInfo) {
    unsigned int i, j, listSize;
    process_t *process;
    arrayList_t *curList, *highList;
    // move priorities up one level 0-14 up one level
    for(i = 0; i < PRIORITY_LEVELS - 2; i++) {
        int higherPriority = i + 1;

        curList = schedulingInfo->processes.list[i];
        highList = schedulingInfo->processes.list[higherPriority];

        if( highList == NULL ) {
            highList = arraylist_create();
        }

        if( curList == NULL ) {
            curList = arraylist_create();
        }

        listSize = arraylist_getsize(highList);
        for(j = 0; j < listSize; j++) {
            process = (process_t*) arraylist_get(curList, j);
            process->currentPriority = higherPriority;
            arraylist_add(highList, process);
            arraylist_remove(curList, j, 1);
        }
    }
}

void swapProcesses(schedulingInfo_t *schedulingInfo) {
    char foundProcess = 0;

    if( schedulingInfo->processes.active != NULL && schedulingInfo->processes.active->ptr != NULL ) {
        schedulingInfo->processes.active->ptr->state = PROCESS_STATE__SUSPENDED;
    }

    // if first iteration or no processes in queue (waiting for more)
    // set active pointer to first one of highest priority
    if( schedulingInfo->processes.active == NULL ) {
        // test if processes still in highest priority level 0-15
        foundProcess = swapProcessesLoop(schedulingInfo, -1, 0, PRIORITY_LEVELS - 1);
    } else {
        // current process is running - set to next highest priority
        int element = schedulingInfo->processes.active->arrayIndex;
        int priority = schedulingInfo->processes.active->priority;
        foundProcess = swapProcessesLoop(schedulingInfo, 1, element, priority);
        if( foundProcess == 0 ) {
            foundProcess = swapProcessesLoop(schedulingInfo, -1, element, priority);
        }
    }

    if( foundProcess == 0 ) {
        schedulingInfo->processes.active = NULL;
    }

    if( schedulingInfo->processes.active != NULL && schedulingInfo->processes.active->ptr != NULL ) {
        schedulingInfo->processes.active->ptr->state = PROCESS_STATE__CPU;
    }
}

/**
 * @param schedulingInfo_t* schedulingInfo
 * @param int incrementer either 1 or -1
 * @param int element set to element offset or 0
 * @param int priority set to starting priority or 0
**/
char swapProcessesLoop(schedulingInfo_t *schedulingInfo, int incrementer, int element, int priority) {
    char foundProcess = 0;
    int i, j;
    size_t priorityListLen;

    for(i = priority; i >= 0 && i < PRIORITY_LEVELS && foundProcess == 0; i += incrementer) {
        priorityListLen = arraylist_getsize(schedulingInfo->processes.list[i]);

        // TODO remove
        // fprintf(stderr, "SIZE[%d]:%d\n\n", i, priorityListLen);
        for(j = element; (unsigned) j < priorityListLen && foundProcess == 0; j++) {
            if( schedulingInfo->processes.active == NULL ) {
                schedulingInfo->processes.active = (processInfo_t*) malloc(sizeof(processInfo_t));
            }
            schedulingInfo->processes.active->priority = i;
            schedulingInfo->processes.active->arrayIndex = j;
            schedulingInfo->processes.active->ptr = (process_t*) arraylist_get(schedulingInfo->processes.list[i], j);
            foundProcess = 1;
        }
    }
    return foundProcess;
}

void printProcessList(schedulingInfo_t *schedulingInfo) {
    int i, priority, listSize;
    for(priority = 0; priority < PRIORITY_LEVELS; priority++) {
        printf("\n---------------------------------------------\n");
        printf("                Priority #%d\n", priority);
        printf("---------------------------------------------\n");
        listSize = arraylist_getsize(schedulingInfo->processes.list[priority]);
        for(i = 0; i < listSize; i++) {
            process_t *process = (process_t*) arraylist_get(schedulingInfo->processes.list[priority], i);
            printf("-------------------Process[%d] Priority[%d]------\n", i, priority);
            printProcessInfo(process);
        }
    }
}

void printProcessInfo(process_t *process) {
    if( process == NULL ) {
        printf("Process is NULL\n");
    } else {
        printf("Process addr:%ld \n", process);
        printf("%-25s:%d\n", "startingPriority", process->startingPriority);
        printf("%-25s:%d\n", "currentPriority", process->currentPriority);
        printf("%-25s:%d\n", "startTime", process->startTime);
        printf("%-25s:%d\n", "runTime", process->runTime);
        printf("%-25s:%d\n", "ioTriggeredInterval", process->ioTriggeredInterval);
        printf("%-25s:%d\n", "ioDuration", process->ioDuration);
        printf("%-25s:%d\n", "timeInCpu", process->timeInCpu);
        printf("%-25s:%d\n", "timeLeftInBlocked", process->timeLeftInBlocked);
        printf("%-25s:%d\n", "timeInReadyQueue", process->timeInReadyQueue);
        printf("%-25s:%d\n", "totalTimeInCpu", process->totalTimeInCpu);
        printf("%-25s:%d\n", "totalTimeInIo", process->totalTimeInIo);
        printf("%-25s:%d\n", "totalTimeInReadyQueue", process->totalTimeInReadyQueue);
        printf("%-25s:%d\n", "smallestTimeInQueue", process->smallestTimeInQueue);
        printf("%-25s:%d\n", "longestTimeInReadyQueue", process->longestTimeInReadyQueue);
        printf("%-25s:%d\n", "state", process->state);
        printf("%-25s:%s\n", "name", process->name);
    }
}

void executeProcess(schedulingInfo_t *schedulingInfo) {
    fprintf(stderr, "ActiveP:%x\n", 1);
    if ( schedulingInfo->processes.active != NULL ) {
        process_t *active = schedulingInfo->processes.active->ptr;
        int priority =  active->currentPriority;
        int index = schedulingInfo->processes.active->arrayIndex;
        // check if process shouldn't be executed yet and thow error
        if( active->state != PROCESS_STATE__CPU ) {
            fprintf(stderr, "Process:'%s' not in valid state:%d\n", active->name, active->state);
        } else {
            active->timeInCpu++;
        }

        // process is completed
        if( active->timeInCpu == active->runTime ) {
            active->state = PROCESS_STATE__COMPLETED;
            arraylist_add(schedulingInfo->processes.completedList, active);
            arraylist_remove(schedulingInfo->processes.list[priority], index, 1);
        }
        // move process into blocked state
        // put process in blocked
        else if ( active->ioTriggeredInterval  ) {
            active->state = PROCESS_STATE__BLOCKED;
            arraylist_add(schedulingInfo->processes.waitingForIoList, active);
            arraylist_remove(schedulingInfo->processes.list[priority], index, 0);
            swapProcesses(schedulingInfo);
        }
        // continue running
        else {
            active->state = PROCESS_STATE__CPU;
        }
    }
}

int main(int argc, char* argv[]) {
    // process list info
    schedulingInfo_t *schedulingInfo = (schedulingInfo_t*) malloc(sizeof(schedulingInfo_t));
    initialize(schedulingInfo);
    createTestProcessList(schedulingInfo);

    uint64_t lastSwap = 0;
    // round robin through processes working from 0-15 priorities
    while( hasProcesses(schedulingInfo) ) {
        fprintf(stderr, "BEFORE queueProcesses \n");
        queueProcesses(schedulingInfo);
        fprintf(stderr, "BEFORE getAction \n");
        if( getAction(schedulingInfo) == ACTION__SWAP) {
            // load new process
            if( schedulingInfo->processes.active != NULL ) {
                schedulingInfo->processes.active->ptr->totalTimeInCpu += schedulingInfo->quantums.current - lastSwap;
            }
            fprintf(stderr, "BEFORE ageProcesses \n");
            ageProcesses(schedulingInfo);
            fprintf(stderr, "BEFORE swapProcesses \n");
            swapProcesses(schedulingInfo);
            lastSwap = schedulingInfo->quantums.current;
        }
        fprintf(stderr, "BEFORE executeProcess \n");
        // fprintf(stderr, "Active:%ld\n", schedulingInfo->processes.active);
        // printProcessInfo(schedulingInfo->processes.active->ptr);
        executeProcess(schedulingInfo);
        // fprintf(stderr, "Active2:%ld\n", schedulingInfo->processes.active);
        // printProcessInfo(schedulingInfo->processes.active->ptr);
        schedulingInfo->quantums.current++;
        // fprintf(stderr, "\n\n");return 0;
        fprintf(stderr, "BEFORE hasProcesses \n");
    }
    printProcessList(schedulingInfo);
    return 0;
}
