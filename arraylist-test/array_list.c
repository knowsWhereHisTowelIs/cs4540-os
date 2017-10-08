#include "array_list.h"
// https://codereview.stackexchange.com/questions/64423/implementing-an-arraylist
// @see https://stackoverflow.com/questions/3732856/arraylist-in-c-not-working

arraylist_t* arraylist_create() {
    printErr("CREATING %d\n", sizeof(arraylist_t));
    arraylist_t *list = (arraylist_t*) malloc(sizeof(arraylist_t));
    assert(list != NULL);
    list->size = 0;

    list->data = NULL;

    // initialize to ARRAYLIST_DEFAULT_SIZE element pointers
    // list->data = (void**) calloc(ARRAYLIST_DEFAULT_SIZE, sizeof(void *));
    // assert(list->data != NULL);
    // list->data[0] = NULL;
    return list;
}

void printArraylist(arraylist_t *list) {
    unsigned int i;
    printErr("PRINTING ARRAY LIST w/ptr:%p size:%d\n", list, list->size);
    for(i = 0; i < list->size; i++) {
        printErr("List[i][%d] ", i);
        elem_t *elem = (elem_t*) arraylist_get(list, i);
        if( elem != NULL ) {
            printErr("ptr:%p num:%d name:'%s'\n", elem, elem->num, elem->str);
        } else {
            printErr("ptr:NULL\n");
        }
    }
}

void arraylist_setdata(arraylist_t *list, void ** data, int max, int clear_data) {
    // Sets the internal array of the arraylist
    if ( clear_data ) {
        arraylist_clear(list);
    }
    list->data = data;
    list->size = max;
}

void arraylist_add(arraylist_t *list, void *elem) {
    // Adds one element of generic pointer type to the internal array
    // void **newData = (void**) realloc(list->data, arraylist_getsizeof(list));
    void **newData = (void**) realloc(list->data, (list->size + 1) * sizeof(void*));
    assert(newData != NULL);
    newData[list->size] = elem;
    arraylist_setdata(list, newData, list->size + 1, 0);
}

void *arraylist_get(arraylist_t *list, int index) {
    // Gets an member of the array at an index
    return list->data[index];
}

size_t arraylist_getsizeof(arraylist_t *list) {
    // Returns the size of the internal array in memory
    return sizeof(*list->data);
}

size_t arraylist_getsize(arraylist_t *list) {
    // Returns the number of elements in the arraylist
    return list->size;
}

// TODO update by programs element
void arraylist_clean_element(arraylist_t *list, int index) {
    elem_t *elem = (elem_t*) arraylist_get(list, index);
    assert(elem != NULL );
    if( elem->str != NULL ) {
        free(elem->str);
    }
}


void arraylist_remove(arraylist_t *list, int index, int freeit) {
    printErr("Removing size %2d index:%d freeit:%d ptr:%p\n", list->size, index, freeit, arraylist_get(list,index));
    for(unsigned int k = 0; k < list->size; k++) {
        printErr("Removing[%d] size %2d index:%d freeit:%d ptr:%p\n", k, list->size, index, freeit, arraylist_get(list,k));
    }
    printErr("\n");
    // clear if remove only element
    if (list->size == 1) {
        arraylist_clear(list);
    }
    // Removes one element at and index
    else if ( (unsigned) index < list->size && index >= 0 ) {
        printErr("***********OLD DATA size:%d\n", list->size);
        printArraylist(list);// TODO
        if (freeit) {
            arraylist_clean_element(list, index);
            elem_t *elem = (elem_t*) arraylist_get(list, index);
            free(elem);
        }
        // move every elemnt after index into low index and set the final value == null
        unsigned int i, newSize;
        newSize = list->size - 1;
        for(i = index; i < list->size; i++) {
            if( i == (list->size-1) ) {
                printErr("Setting[%d] null\n", i);
                list->data[i] = NULL;
            } else {
                printErr("Setting[%d] old:%p new:%p", i, list->data[i], list->data[i+1]);
                list->data[i] = list->data[i + 1];
                printErr(" FINAL:%p num:%d\n", list->data[i], ((elem_t*)list->data[i])->num);
            }
        }
        //copy old data to new location with updated size
        void **newData = (void**) realloc(list->data, newSize * sizeof(void*));
        assert(newData != NULL);

        //update arraylist ptr to use new data
        list->data = newData;
        list->size--;
        printErr("***********FINAL DAT size:%d\n", list->size);
        printArraylist(list);// TODO
    }
}

void arraylist_clear(arraylist_t *list) {
    // Clears the internal array
    // Free LIST seperatly
    /*
    list->size = 0;
    if( list->data != NULL ) {
        free(list->data);
        list->data = NULL;
    }
    */
    if( list->data != NULL ) {
        // TODO update this section for the assocaited elements
        int i;
        for(i = 0; (unsigned) i < list->size; i++) {
            elem_t *elem = (elem_t*) arraylist_get(list, i);
            arraylist_clean_element(list, i);
            free(elem);
        }
        free(list->data);
    }
    list->size = 0;
}

void arraylist_deallocate(arraylist_t *list) {
    // De-allocates the arraylist from memory No usage of the arraylist is allowed after this function call
    if (list->data != NULL) {
        free(list->data);
        list->data = NULL;
    }
    free(list);
}

int arraylist_getindex(arraylist_t *list, void *elem) {
    // Looks for elem in list and returns the index or -1 if not found
    for(int i = 0; (unsigned int) i < list->size; ++i) {
        if (elem == arraylist_get(list, i)) {
            return i;
        }
    }
    return -1;
}
