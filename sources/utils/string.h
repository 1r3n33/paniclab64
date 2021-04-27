#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include <nusys.h>

typedef struct
{
    char buf[32];
    char *p;
    s32 w;
    s32 x;
    s32 y;
} String;

#endif // UTILS_STRING_H
