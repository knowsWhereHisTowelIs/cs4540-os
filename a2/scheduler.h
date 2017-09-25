#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "process.h"
// #include "priority_queue.h"
#include "array_list.h"

#ifndef MAIN_C
#define MAIN_C

    // ================= DEFINITIONS ====================
    //processes 0-15 with three on each
    #define SCHEDULER_MAX_PROCESSES 48
    #define PRIORITY_LEVELS 16 // 0 -15
    #define TIME_QUANTUM 16
    // After the set amount of time passes increase the priority of all processes
    #define TIME_QUANTUM_TO_AGE 256

    // ================= TYPEDEFS ====================
    typedef struct {
        // counter of processes  generated
        int created;
        //
        arrayList_t **processes;
        // current active process
        struct activeProcess {
            process_t *ptr;
            int priority;
            int arrayIndex;
        };
        // list of processes waiting for IO
        int waitingForIo[ SCHEDULER_MAX_PROCESSES ];
    } schedulingInfo_t;
    // ================= PROTOTYPES ====================
    int main(int argc, char* argv[]);
    void initialize(schedulingInfo_t *schedulingInfo, arrayList_t **processes, process_t *activeProcess, int *priorityIndex);
    void initProcessList(arrayList_t **processes);
    void createTestProcessList(arrayList_t **processes, schedulingInfo_t *schedulingInfo);
    void printProcessInfo(arrayList_t **processes, schedulingInfo_t *schedulingInfo);
    void setActiveProcess(arrayList_t **processes, process_t *process, int *priorityIndex);
    void createProcess(arrayList_t **processes, schedulingInfo_t *schedulingInfo);
    void executeProcess(process_t *processes);
    void swapProcesses(arrayList_t **processes);
    void ageProcesses(arrayList_t **processes);
    char hasProcesses(arrayList_t **processes);
#endif
