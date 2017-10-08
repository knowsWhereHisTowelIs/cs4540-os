#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "def.h"

#ifndef ARRAYLIST_H
    #define ARRAYLIST_H
    // ======================== DEFINITIONS ====================================
    #define ARRAYLIST_DEFAULT_SIZE 2
    // ======================== TYPEDEFS =======================================
    typedef struct {
        size_t size;
        void ** data;
    } arraylist_t;
    // ======================== PROTOTYPES =====================================

    arraylist_t* arraylist_create();

    void arraylist_setdata(arraylist_t *list, void ** data, int max, int clear_data);
    void arraylist_add(arraylist_t *list, void *elem);
    void *arraylist_get(arraylist_t *list, int index);
    size_t arraylist_getsizeof(arraylist_t *list);
    size_t arraylist_getsize(arraylist_t *list);
    void arraylist_remove(arraylist_t *list, int index, int freeit);
    void arraylist_clear(arraylist_t *list);
    void arraylist_deallocate(arraylist_t *list);
    int arraylist_getindex(arraylist_t *list, void *elem);

#endif
