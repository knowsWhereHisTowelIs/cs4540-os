#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "process.h"
#include "priority_queue.h"

#ifndef MAIN_C
#define MAIN_C

    // ================= DEFINITIONS ====================
    //processes 0-15 with three on each
    #define SCHEDULER_MAX_PROCESSES 48
    #define PRIORITY_LEVELS 16 // 0 -15
    #define TIME_QUANTUM 8

    // ================= TYPEDEFS ====================
    typedef struct {
        // counter of processes  generated
        int created;
        // processes list active index
        int activeProcess;
        // list of processes waiting for IO
        int waitingForIo[ SCHEDULER_MAX_PROCESSES ];
    } processList_t;
    // ================= PROTOTYPES ====================
    int main(int argc, char* argv[]);
    void initialize(processList_t *processList);

    void createTestProcessList(heap_t *processes, processList_t *processList);
    void printProcessInfo(heap_t *processes, processList_t *processList);

    void createProcess(heap_t *processes, processList_t *processList);
    char hasProcesses();
    void swapProcesses();
    void executeActiveProcess();
    void ageProcesses();
    char hasProcesses();
#endif
