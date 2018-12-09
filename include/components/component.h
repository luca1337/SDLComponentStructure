#ifndef COMPONENT_H
#define COMPONENT_H

#define GET_SIZE(x) sizeof(x)

#include <utils.h>

typedef struct component{
    struct component* next;
    struct component* prev;
    char* name;
    char started, active;
    void(*tick)(struct component* comp);
    void(*begin)(struct component* comp);
    void(*destroy)(struct component* comp);
    void(*set_name)(struct component*, const char* new_name);
}component_t;

component_t* component_new(const char* name, int size);

#endif