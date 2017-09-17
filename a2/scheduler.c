/**
 * @author: Caleb Slater
 * @class: ECE 4540
 * @assignment: 2
**/
#include "scheduler.h"
#include "process.h"

// priorities 0-15 with 0 lowest
// 3 processes for each priority, 1 just CPU, 1 evenly CPU & IO bound, 1 that is just IO
// round robin algorithim

//data structures - name, start priority, current priority w/aging
// priorityQueue of ready processes
// list of processes waiting for IO
// struct of OS params common to all processes, max time in CPU w/o bumped, max wait time

extern processType processes[ SCHEDULER_MAX_PROCESSES ];

// processes list active index
int activeProcess = 0;

// counter of processes randomly generated
int processesCreated = 0;

// list of processes waiting for IO
int processWaitingForIo[ SCHEDULER_MAX_PROCESSES ];

int main(int argc, char* argv[]) {
    while( hasProcesses() ) {
        // create processes until the predecided 48 have been created
        if( processesCreated < SCHEDULER_MAX_PROCESSES ) {
            createProcess();
        }
        swapProcesses();
        executeActiveProcess();
        //TODO maybe change location of ageProcesses
        ageProcesses();
    }
    // program ran successfully
    return 0;
}

void createProcess() {
    processesCreated++;
}

void swapProcesses() {

}

void executeActiveProcess() {
    processType process = processes[activeProcess];
}

void ageProcesses() {

}
