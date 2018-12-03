#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdio.h>

#define NO_MEM -1
#define OK 0
#define UNKNOWN 2

#define strcat_macro(str1, str2) #str1 "" #str2

#define CHECK_RET(x, y, msg) if(!x){\
    fprintf(stderr, strcat_macro(msg, "\n"));\
    return y;\
}\

#define SDL_LOG(x, y) if(!x){\
    SDL_Log("[%s]", SDL_GetError());\
    return y;\
}\

#endif