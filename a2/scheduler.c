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
    // heap array of processes based on priority 0-15
    arrayList_t **processes = (arrayList_t**) malloc(sizeof(arrayList_t) * PRIORITY_LEVELS);
    int i;
    for( i = 0; i < PRIORITY_LEVELS; i++) {
        processes[i] = arraylist_create();
    }
    // arrayList_t processes[PRIORITY_LEVELS];
    // process list info
    processList_t processList;

    initialize(&processList);

    //start debugging
    createTestProcessList(&processes[0], &processList);
    for(i = 0; i < PRIORITY_LEVELS; i++ ) {
        printf("%d\n", i);
    }
    printProcessInfo(&processes[0], &processList);
    printf("\n\nExited fine\n\n");
return 0;

    while( hasProcesses() ) {
        // create processes until the predecided 48 have been created
        if( processList.created < SCHEDULER_MAX_PROCESSES ) {
            // createProcess(processes[0], &processList);
        }
        swapProcesses();
        executeActiveProcess();
        //TODO maybe change location of ageProcesses
        ageProcesses();
    }
    // program ran successfully
    return 0;
}

void initialize(processList_t *processList) {
    processList->created = 0;
    processList->activeProcess = 0;
}

void createTestProcessList(arrayList_t **processes, processList_t *processList) {
    for(int priority = 0; priority < PRIORITY_LEVELS; priority++ ) {
        for(int i = 0; i < 1; i++) {
            processList->created++;
            process_t *process;
            char *name;
            // allocate 32 bytes for the string and populate with null
            name = (char*) calloc(sizeof(char), 32);
            sprintf(name, "Process #:%d", processList->created);

            // random int from 1 to 100
            int ioInBetweenTime = (priority * 100) + (i * 10) + 1;
            int ioDuration      = (priority * 100) + (i * 10) + 1;
            populateProcess(
                process, name, priority, ioInBetweenTime, ioDuration
            );
            printf("\n\nPOPULATED pri:%d[%d], %s, ioInBetweenTime:%d ioDuration:%d\n", priority, i, name, ioInBetweenTime, ioDuration);
            printf("PROCESSES %p\n", (void*) processes);
            arraylist_add(processes[priority], process);
            // arraylist_add(processes, &process);
        }
    }
    printf("\ncreateTestProcessList end\n");
}

void printProcessInfo(arrayList_t **processes, processList_t *processList) {
    for(int priority = 0; priority < PRIORITY_LEVELS; priority++) {
        for( int i = 0; i < 4; i++) {
            // process_t *process = (process_t*) arraylist_get(&processes[priority], i);
            // printf("Process priority:%d[%d]\n", process->startingPriority, i);
        }
    }
    // exit(0);
}

void createProcess(arrayList_t *processes, processList_t *processList) {
    process_t process;

    processList->created++;

    char *name;
    // allocate 32 bytes for the string and populate with null
    name = (char*) calloc(sizeof(char), 32);
    sprintf(name, "Process #:%d", processList->created);

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

char hasProcesses() {
    return 1;
}

void swapProcesses() {

}

void executeActiveProcess() {
    //processType process = processes[activeProcess];
}

void ageProcesses() {

}
