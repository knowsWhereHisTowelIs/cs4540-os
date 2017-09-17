
#ifndef PROCESS_H
    #define PROCESS_H
    // ======================== DEFINITIONS ====================================
    // ======================== TYPEDEFS =======================================
    typedef struct {
        // Name of process
        char* name[];
        // Starting priority, reset current priority to this each time process moved into wait queue, does not change.
        char startingPriority;
        // Current priority of the process which may change with aging.
        char currentPriority;
        //Time in CPU needed before/between I/O (set once)
        //Time I/O takes (set once)
        //Total time in machine not counting time in wait queue (set at startup counts down).  How much time process spends doing something before it exits.  Sum of total time in CPU and total time in I/O.
        //Time in CPU currently.  Set to 0 when moved into CPU, when reaches A or quantum is up moves out of CPU.
        //Time left waiting for current I/O
        //Time process has been waiting in ready queue
        //Total time in CPU
        //Total time in I/O
        //Total time in ready queue
        //Smallest time in ready queue
        //Longest time in ready queue
        //  You need to keep track of the current state of each process; you might have a field in each process or use which data structure it is in.  In CPU, I/O wait, Ready queue ….
    } processType;

    // ======================== PROTOTYPES =====================================
    bool hasProcesses();
#endif
