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
    void(*actor_set_scale)(struct actor* actor, const vec2_t* scale);
    void(*actor_set_position)(struct actor* actor, const vec2_t* position);
    void(*actor_set_rotation)(struct actor* actor, const float* rotation);
}actor_t;

void actor_new(actor_t* actor, const char*);
int add_component(actor_t*, component_t*);
int get_component(actor_t*, const char*, component_t**);
component_t* get_component_by_name(actor_t*, const char*);
void set_name(actor_t* actor, const char* name);

#endif