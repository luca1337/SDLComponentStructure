#ifndef ACTOR_H
#define ACTOR_H

#include <transform.h>
#include <component.h>
#include <vec.h>

typedef struct actor{
    char* name;
    struct component* c_head;
    struct component* c_tail;
    struct actor* next;
    struct actor* prev;
    transform_t transform;
}actor_t;

actor_t* actor_new(const char*);
int add_component(actor_t*, component_t*);
int get_component(actor_t*, const char*, component_t**);

#endif