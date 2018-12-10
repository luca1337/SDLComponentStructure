#ifndef BOUNCE_COMPONENT_H
#define BOUNCE_COMPONENT_H

#include <actor.h>
#include <moveball_component.h>

typedef struct bounce_component{
    component_t component;
    actor_t* actor;
    void* player;
    moveball_component_t* moveball_ref;
}bounce_component_t;

void bounce_component_init(bounce_component_t*, actor_t*);

#endif