#include <stdlib.h>
#include <assert.h>

#ifndef ARRAY_LIST_C
    #define ARRAY_LIST_C
    // ======================== DEFINITIONS ====================================
    // ======================== TYPEDEFS =======================================
    typedef struct {
        size_t size;
        void ** data;
    } arrayList_t;
    // ======================== PROTOTYPES =====================================

    arrayList_t* arraylist_create();

    void arraylist_setdata(arrayList_t *list, void ** data, int max, int clear_data);
    void arraylist_add(arrayList_t *list, void *elem);
    void *arraylist_get(arrayList_t *list, int index);
    size_t arraylist_getsizeof(arrayList_t *list);
    size_t arraylist_getsize(arrayList_t *list);
    void arraylist_remove(arrayList_t *list, int index, int freeit);
    void arraylist_clear(arrayList_t *list);
    void arraylist_deallocate(arrayList_t *list);
    int arraylist_getindex(arrayList_t *list, void *elem);

#endif
