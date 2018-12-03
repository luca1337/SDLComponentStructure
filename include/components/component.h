#ifndef COMPONENT_H
#define COMPONENT_H

#include <utils.h>

typedef struct component{
    struct component* next;
    struct component* prev;
    char* name;
    char started, active;
    void(*tick)(struct component*);
    void(*begin)(struct component*);
    void(*destroy)(struct component*);
}component_t;

component_t* component_new(const char* name);

#endif