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
    // array of processes based on priority 0-15
    arrayList_t **processes = (arrayList_t**) malloc(sizeof(arrayList_t) * PRIORITY_LEVELS);
    // completed processes
    arrayList_t *completedProcesses = (arrayList_t*) malloc(sizeof(arrayList_t));
    // process list info
    schedulingInfo_t *schedulingInfo;
    process_t *activeProcess;

    int priorityIndex;
    initialize(schedulingInfo, &processes[0], activeProcess, &priorityIndex);

    //TODO remove
    createTestProcessList(&processes[0], schedulingInfo);

    // setActiveProcess(&processes[0], activeProcess, priorityIndex);
    // round robin through processes working from 0-15 priorities
    while( hasProcesses(&processes[0]) ) {
        // int action; ///todo
        // switch( action ) {
        //     case ACTION__PROCESS_SWAP:
        //         ageProcesses(&processes[0]);
        //         setActiveProcess(&processes[0], activeProcess, schedulingInfo);
        //     case ACTION__EXECUTE:
        //     default:
        //         break;
        // }
        executeProcess(activeProcess);
        if( activeProcess->state == PROCESS_STATE__COMPLETED ) {

        }
        swapProcesses(&processes[0]);
    }
    printProcessInfo(&processes[0], schedulingInfo);
    // program ran successfully
    return 0;
}

void initialize(schedulingInfo_t *schedulingInfo, arrayList_t **processes) {
    schedulingInfo->created = 0;
    schedulingInfo->activeProcess = 0;
    initProcessList(processes);
    setActiveProcess(&processes[0], schedulingInfo);
}

void initProcessList(arrayList_t **processes) {
    int i;
    for( i = 0; i < PRIORITY_LEVELS; i++) {
        processes[i] = arraylist_create();
    }
}

void createTestProcessList(arrayList_t **processes, schedulingInfo_t *schedulingInfo) {
    //TODO remove
    printf("\n---------------Creating Process List---------------------------");

    for(int priority = 0; priority < PRIORITY_LEVELS; priority++ ) {
        for(int i = 0; i < 1; i++) {
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
            printf("\nPOPULATED pri:%d[%d], %s, ioInBetweenTime:%d ioDuration:%d", priority, i, name, ioInBetweenTime, ioDuration);
            arraylist_add(processes[priority], process);
            // arraylist_add(processes, &process);
        }
    }
}

void printProcessInfo(arrayList_t **processes, schedulingInfo_t *schedulingInfo) {
    for(int priority = 0; priority < PRIORITY_LEVELS; priority++) {
        for( int i = 0; i < 4; i++) {
            process_t *process = (process_t*) arraylist_get(processes[priority], i);
            printf("Process priority:%d[%d]\n", process->startingPriority, i);
        }
    }
    // exit(0);
}

void createProcess(arrayList_t **processes, schedulingInfo_t *schedulingInfo) {
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

void setActiveProcess(arrayList_t **processes, process_t *process, int *priorityIndex) {

}

void executeProcess(process_t *processes) {
    //processType process = processes[activeProcess];
}

void swapProcesses(arrayList_t **processes) {

}

void ageProcesses(arrayList_t **processes) {
    int i;
    int originalProcessesPriOneSize = processes[1]->size;
    process_t *process;

    // iterate over all elements of priority 1
    // move from priority 1 to priority 0
    for(i = 0; i < originalProcessesPriOneSize; i++) {
        process = (process_t*) arraylist_get(processes[1], 0);
        arraylist_add(processes[0], process);
        arraylist_remove(processes[1], 0, 1);
    }

    // move all priorities up one level
    for(i = 2; i < PRIORITY_LEVELS; i++) {
        int higherPriority = i - 1;
        processes[higherPriority] = processes[i];
        processes[i] = NULL;
    }
}

char hasProcesses(arrayList_t **processes) {
    return 1;
}
