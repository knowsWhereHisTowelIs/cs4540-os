#include "priority_queue.h"
// modified from https://rosettacode.org/wiki/Priority_queue#C

void priority_queue_push(heap_t *heapPtr, node_t *nodePtr) {
    // if the heapPtr size needs to be increased malloc more memory
    heapPtr->len++;
    if( heapPtr->len >= heapPtr->size ) {
        heapPtr->size = heapPtr->size ? heapPtr->size * 2 : 4;
        heapPtr->nodes = (node_t*) realloc(heapPtr->nodes, heapPtr->size * sizeof(node_t));
    }

    // search down heap for new position and adjust other references
    int i = heapPtr->len + 1;
    int j = i / 2;
    while( i > 1 && heapPtr->nodes[j].priority > nodePtr->priority ) {
        heapPtr->nodes[i] = heapPtr->nodes[j];
        i = j;
        j /= 2;
    }
    heapPtr->nodes[i] = *nodePtr;
}

node_t* priority_queue_pop(heap_t *heapPtr) {
    int i, j, k;
    if ( ! heapPtr->len ) {
        return NULL;
    }

    heapPtr->nodes[1] = heapPtr->nodes[heapPtr->len];
    heapPtr->len--;
    i = 1;
    while (1) {
        k = i;
        j = 2 * i;
        if (j <= heapPtr->len && heapPtr->nodes[j].priority < heapPtr->nodes[k].priority) {
            k = j;
        }
        if (j + 1 <= heapPtr->len && heapPtr->nodes[j + 1].priority < heapPtr->nodes[k].priority) {
            k = j + 1;
        }
        if (k == i) {
            break;
        }
        heapPtr->nodes[i] = heapPtr->nodes[k];
        i = k;
    }
    heapPtr->nodes[i] = heapPtr->nodes[heapPtr->len + 1];
    return &heapPtr->nodes[i];
}
