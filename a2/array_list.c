#include "array_list.h"
// https://codereview.stackexchange.com/questions/64423/implementing-an-arraylist
// @see https://stackoverflow.com/questions/3732856/arraylist-in-c-not-working

arrayList_t* arraylist_create() {
    arrayList_t *list = (arrayList_t*) malloc(sizeof(arrayList_t));
    if (list == NULL) {
        return NULL;
    }

    list->size = 0;
    // initialize to ARRAYLIST_DEFAULT_SIZE element pointers
    list->data = (void**) calloc(ARRAYLIST_DEFAULT_SIZE, sizeof(void *));
    if (list->data == NULL) {
        free(list); // Don't leek memory here!
        return NULL;
    }

    return list;
}

void arraylist_setdata(arrayList_t *list, void ** data, int max, int clear_data) {
    // Sets the internal array of the arraylist
    if ( clear_data ) {
        arraylist_clear(list);
    }
    list->data = data;
    list->size = max;
}

void arraylist_add(arrayList_t *list, void *elem) {
    // Adds one element of generic pointer type to the internal array
    // void **new_data = (void**) realloc(list->data, arraylist_getsizeof(list));

    // void **new_data = (void**) malloc(arraylist_getsizeof(list) + sizeof(elem));
    // for(int i = 0; i < list->size; i++) {
    //     new_data[i] = list->data[i];
    // }
    // new_data[list->size] = elem;

    // assert(new_data != NULL);
//    list->data[list->size] = elem;
//    arraylist_setdata(list, list->data, list->size + 1, 0);

    int size = arraylist_getsize(list);
    void **new_data;
    new_data = realloc(list->data, (size + 1) * sizeof new_data[0]);
    if (new_data) {
        new_data[size] = elem;
        list->data = new_data;
        list->size++;
    }
}

void *arraylist_get(arrayList_t *list, int index) {
    // Gets an member of the array at an index
    return list->data[index];
}

size_t arraylist_getsizeof(arrayList_t *list) {
    // Returns the size of the internal array in memory
    return sizeof(*list->data);
}

size_t arraylist_getsize(arrayList_t *list) {
    // Returns the number of elements in the arraylist
    return list->size;
}

void arraylist_remove(arrayList_t *list, int index, int freeit) {
    // Removes one element at and index
    if ( (unsigned int) index > ( list->size - 1 ) ) {
        return;
    }
    if ( list->size == 1) {
        arraylist_clear(list);
        return;
    }
    if (freeit) {
        free(arraylist_get(list, index));
    }
    for ( int i = index; (unsigned int) i < list->size; ++i ) {
        if ( (unsigned int) i == list->size - 1) {
            list->data[i] = NULL;
        } else {
            list->data[i] = list->data[i + 1];
        }
    }
    fprintf(stderr, "\nB4 Realloc");

    void **new_data = (void**) realloc(list->data, arraylist_getsizeof(list));
    list->size--;
    assert(new_data != NULL);
    arraylist_setdata(list, new_data, list->size, 0);

//    --list->size;
//    arraylist_setdata(list, list->data, list->size, 0);

}

void arraylist_clear(arrayList_t *list) {
    // Clears the internal array
    list->size = 0;
    free(list->data);
    list->data = NULL;
}

void arraylist_deallocate(arrayList_t *list) {
    // De-allocates the arraylist from memory No usage of the arraylist is allowed after this function call
    if (list->data != NULL)
        free(list->data);
    free(list);
}

int arraylist_getindex(arrayList_t *list, void *elem) {
    // Looks for elem in list and returns the index or -1 if not found
    for(int i = 0; (unsigned int) i < list->size; ++i)
        if (elem == arraylist_get(list, i))
            return i;
    return -1;
}
