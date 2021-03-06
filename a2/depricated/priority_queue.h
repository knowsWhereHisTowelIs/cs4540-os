// modified from https://rosettacode.org/wiki/Priority_queue#C
#include <stdio.h>
#include <stdlib.h>

#ifndef PRIORITY_QUEUE_H
    #define PRIORITY_QUEUE_H
    // ======================== DEFINITIONS ====================================
    // ======================== TYPEDEFS =======================================
    typedef struct {
        int priority;
        char *data;
    } node_t;

    typedef struct {
        node_t *nodes;
        int len;
        int size;
    } heap_t;
    // ======================== PROTOTYPES =====================================
    void priority_queue_push(heap_t *heapPtr, node_t *nodePtr);
    node_t* priority_queue_pop(heap_t *heap);
#endif
