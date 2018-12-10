#ifndef MOVEBALL_COMPONENT_H
#define MOVEBALL_COMPONENT_H

#include <vec.h>
#include <actor.h>
#include <vec.h>

enum dir{
    STOP = 0,
    UP_RIGHT = 1,
    UP_LEFT = 2,
    DOWN_RIGHT = 3,
    DOWN_LEFT = 4,
    ENUM_END = 5
};

typedef struct moveball_component{
    component_t component;
    actor_t* actor;
    vec2_t current_direction;
    void* player;
}moveball_component_t;

void moveball_component_init(moveball_component_t*, actor_t*);

#endif