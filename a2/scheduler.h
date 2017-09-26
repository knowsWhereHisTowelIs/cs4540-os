#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
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
    #define TIME_QUANTUM_BETWEEN_AGING 256
    // scheduler actions
    #define ACTION__BLOCK -1
    #define ACTION__SWAP 1
    #define ACTION__EXECUTE 2

    // ================= TYPEDEFS ====================
    typedef struct {
        process_t *ptr;
        int priority;
        int arrayIndex;
    } processInfo_t;

    typedef struct {
        // increases once per loop
        struct {
            uint64_t current;
            uint64_t lastSwap;
            uint64_t lastAge;
        } quantums;
        // counter of processes generated
        int created;
        // process info struct
        struct {
            // current active process
            processInfo_t *active;
            // list of `process_t`
            arrayList_t **list;
            // list of `process_t` completed list
            arrayList_t *completedList;
            // list of `processInfo_t` processes waiting for IO
            arrayList_t *waitingForIoList;
        } processes;
    } schedulingInfo_t;
    // ================= PROTOTYPES ====================
    int main(int argc, char* argv[]);
    void initialize(schedulingInfo_t *schedulingInfo);
    void createTestProcessList(schedulingInfo_t *schedulingInfo);
    void printProcessInfo(schedulingInfo_t *schedulingInfo);
    void createProcess(schedulingInfo_t *schedulingInfo);
    void executeProcess(schedulingInfo_t *schedulingInfo);
    void swapProcesses(schedulingInfo_t *schedulingInfo);
    char swapProcessesLoop(schedulingInfo_t *schedulingInfo, int incrementer, int element, int priority);
    void ageProcesses(schedulingInfo_t *schedulingInfo);
    char hasProcesses(schedulingInfo_t *schedulingInfo);
    char getAction(schedulingInfo_t *schedulingInfo);
#endif
