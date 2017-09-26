/**
 * @author: Caleb Slater
 * @class: ECE 4540
 * @assignment: 2
**/
#include "scheduler.h"

// priorities 0-15 with 0 lowest
// 3 processes for each priority, 1 just CPU, 1 evenly CPU & IO bound, 1 that is just IO
// round robin algorithim

//data structures - name, start priority, current priority w/aging
// priorityQueue of ready processes
// list of processes waiting for IO
// struct of OS params common to all processes, max time in CPU w/o bumped, max wait time

int main(int argc, char* argv[]) {
    // process list info
    schedulingInfo_t *schedulingInfo = (schedulingInfo_t*) malloc(sizeof(schedulingInfo_t*));

    //TODO remove most printfs
    fprintf(stderr, "Before initialize\n");
    initialize(schedulingInfo);
    fprintf(stderr, "After initialize\n");
    //TODO remove
    createTestProcessList(schedulingInfo);
    fprintf(stderr, "After createTestProcessList\n");

    // load first process
    swapProcesses(schedulingInfo);
    // round robin through processes working from 0-15 priorities
    while( hasProcesses(schedulingInfo) ) {
        switch( getAction(schedulingInfo) ) {
            case ACTION__SWAP:
                ageProcesses(schedulingInfo);
                swapProcesses(schedulingInfo);
                executeProcess(schedulingInfo);
                break;
            case ACTION__EXECUTE:
                executeProcess(schedulingInfo);
                break;
            default:
                fprintf(stderr, "Invalid action\n");
                break;
        }
        // if( activeProcess->state == PROCESS_STATE__COMPLETED ) {
        //
        // }
        // increment the time quantum for round robin
        schedulingInfo->quantums.current++;
    }

    // printProcessInfo(schedulingInfo);
    // printf("After printProcessInfo\n");
    return 0;
}

void initialize(schedulingInfo_t *schedulingInfo) {
    int i;
    schedulingInfo->quantums.current = 0;
    schedulingInfo->quantums.lastSwap = 0;
    schedulingInfo->quantums.lastAge = 0;

    schedulingInfo->created = 0;
    // array of processes based on priority 0-15
    schedulingInfo->processes.list = (arrayList_t**) malloc(sizeof(arrayList_t) * PRIORITY_LEVELS);
    for( i = 0; i < PRIORITY_LEVELS; i++) {
        schedulingInfo->processes.list[i] = arraylist_create();
    }
    // initialize array of process list
    schedulingInfo->processes.completedList = arraylist_create();
    schedulingInfo->processes.waitingForIoList = arraylist_create();
}

void createTestProcessList(schedulingInfo_t *schedulingInfo) {
    //TODO remove
    // fprintf(stderr, "---------------Creating Process List---------------------------");

    for(int priority = 0; priority < PRIORITY_LEVELS; priority++ ) {
        for(int i = 0; i < 4; i++) {
            schedulingInfo->created++;
            process_t *process;
            char *name;
            // allocate 32 bytes for the string and populate with null
            name = (char*) calloc(sizeof(char), 32);
            sprintf(name, "Process #:%d", schedulingInfo->created);

            // random int from 1 to 100
            int ioInBetweenTime = (priority * 100) + (i * 10) + 1;
            int ioDuration      = (priority * 100) + (i * 10) + 1;
            populateProcess(
                process, name, priority, ioInBetweenTime, ioDuration
            );
            // TODO remove
            // fprintf(stderr, "POPULATED pri:%d[%d], %s, ioInBetweenTime:%d ioDuration:%d\n", priority, i, name, ioInBetweenTime, ioDuration);
            arraylist_add(schedulingInfo->processes.list[priority], process);
        }
    }
}

void printProcessInfo(schedulingInfo_t *schedulingInfo) {
    for(int priority = 0; priority < PRIORITY_LEVELS; priority++) {
        for( int i = 0; i < 4; i++) {
            process_t *process = (process_t*) arraylist_get(schedulingInfo->processes.list[priority], i);
            fprintf(stderr, "Process priority:%d[%d]\n", process->startingPriority, i);
        }
    }
}

void createProcess(schedulingInfo_t *schedulingInfo) {
    process_t process;

    schedulingInfo->created++;

    char *name;
    // allocate 32 bytes for the string and populate with null
    name = (char*) calloc(sizeof(char), 32);
    sprintf(name, "Process #:%d", schedulingInfo->created);

    // set a random starting priority
    // if priority already has all needed find next available priority
    int index, startingIndex;
    index = rand() % PRIORITY_LEVELS; // select random priority 0-15
    //TODO finish
    for(startingIndex = index; startingIndex != index; index++) {
        // if
    }
    char startingPriority = 0;

    // random int from 1 to 100
    int ioInBetweenTime = (rand() % 100) + 1;
    int ioDuration = (rand() % 100) + 1;

    populateProcess(
        &process, name, startingPriority, ioInBetweenTime, ioDuration
    );
}

void executeProcess(schedulingInfo_t *schedulingInfo) {

}

void swapProcesses(schedulingInfo_t *schedulingInfo) {
    // if first iteration or no processes in queue (waiting for more)
    // set active pointer to first one of highest priority
    if( schedulingInfo->processes.active->ptr == NULL ) {
        // test if processes still in highest priority level 0-15
        swapProcessesLoop(schedulingInfo, 1, 0, 0);
    } else {
        // current process is running - set to next highest priority
        char foundProcess = 0;
        int element = schedulingInfo->processes.active->arrayIndex;
        int priority = schedulingInfo->processes.active->priority;
        foundProcess = swapProcessesLoop(schedulingInfo, 1, element, priority);
        if( foundProcess == 0 ) {
            foundProcess = swapProcessesLoop(schedulingInfo, -1, element, priority);
        }
        if( foundProcess == 0 ) {
            // TODO remove
            fprintf(stderr, "\nSetting active process to null");
            schedulingInfo->processes.active = NULL;
        }
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
        for(j = element; (unsigned) j < priorityListLen && foundProcess == 0; j++) {
            schedulingInfo->processes.active->priority = i;
            schedulingInfo->processes.active->arrayIndex = j;
            schedulingInfo->processes.active->ptr = (process_t*) arraylist_get(schedulingInfo->processes.list[i], j);
            foundProcess = 1;
        }
    }
    return foundProcess;
}

void ageProcesses(schedulingInfo_t *schedulingInfo) {
    int i;
    int originalProcessesPriOneSize = schedulingInfo->processes.list[1]->size;
    process_t *process;

    // iterate over all elements of priority 1
    // move from priority 1 to priority 0
    for(i = 0; i < originalProcessesPriOneSize; i++) {
        process = (process_t*) arraylist_get(schedulingInfo->processes.list[1], 0);
        arraylist_add(schedulingInfo->processes.list[0], process);
        arraylist_remove(schedulingInfo->processes.list[1], 0, 1);
    }
    // move all priorities up one level
    for(i = 2; i < PRIORITY_LEVELS; i++) {
        int higherPriority = i - 1;
        schedulingInfo->processes.list[higherPriority] = schedulingInfo->processes.list[i];
        schedulingInfo->processes.list[i] = NULL;
    }
}

char hasProcesses(schedulingInfo_t *schedulingInfo) {
    int completed = arraylist_getsize(schedulingInfo->processes.completedList);
    return (completed == schedulingInfo->created) ? 0 : 1;
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
