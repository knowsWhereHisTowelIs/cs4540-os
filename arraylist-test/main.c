#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>
#include "def.h"
#include "array_list.h"

#define ROWS 16
#define ELEMS 8

int counter;

elem_t* getElem() {
    elem_t *elem = (elem_t*) malloc(sizeof(elem_t));
    // char b[50];
    elem->num = counter;
    elem->str = (char*) calloc(sizeof(char), 50);
    sprintf(elem->str, "ELEM counter:%d", counter);
    counter++;
    return elem;
}

void populateArr(arraylist_t **list) {
    int i, j;
    for(i = 0; i < ROWS; i++) {
        printErr("Creating Array %d\n", i);
        list[i] = (arraylist_t*) arraylist_create();
        for(j = 0; j < ELEMS; j++) {
            elem_t *elem = getElem();
            arraylist_add(list[i], elem);
        }
        // break;// TODO
        if( i % 2 == 0 ) {
            int size = 2;//list[i]->size;
            for(j = 0; j < size; j++) {
                printErr("\n////////////////////////////////REMOVE LOOP\n");
                elem_t *elem;
                elem = (elem_t*) arraylist_get(list[i], 0);
                printErr("Removing list[%d][%d] %p\n", i, j, elem);
                arraylist_remove(list[i], 0, 1);
                elem = getElem();
                arraylist_add(list[i], elem);
            }
        }
        printErr("List[%d]=>size:%d\n", i, list[i]->size);
    }
}

void printArr(arraylist_t **list) {
    for(int i = 0; i < ROWS; i++) {
        // if( i % 2 == 0 ) {
        //     printErr("\n");
        // }
        for(int j = 0; j < ELEMS; j++) {
            elem_t *elem = (elem_t*) arraylist_get(list[i], j);
            printErr("PRINTING:> List[%d][%d] PTR:%p I:%2d STR:'%s'\n", i, j, elem, elem->num, elem->str);
        }
        break; // TODO
    }
}

void clean(arraylist_t** list) {
    int i;
    for(i = 0; i < ROWS; i++) {
        arraylist_clear(list[i]);
        free(list[i]);
        // break; // TODO
    }
    free(list);
}

int main(void) {
    counter = 0;
    arraylist_t** list = (arraylist_t**) malloc(sizeof(arraylist_t*) * ROWS * ELEMS);

    printErr("\n*************************POPULATE ARR*******************\n");
    populateArr(list);
    printErr("\n*************************PRINT ARR*******************\n");
    printArr(list);
    printErr("\n*************************CLEAN*******************\n");
    clean(list);

    printErr("\n*************************FINISHED*******************\n");
    return 0;
}
