#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef DEF_H
    #define DEF_H

    typedef struct {
        int num;
        char *str;
    } elem_t;

    void printErr(const char *fmt, ...);

#endif
