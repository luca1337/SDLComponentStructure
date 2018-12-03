#pragma once

#include <actor.h>

typedef struct moveup_component{
    component_t component;
    actor_t* actor;
    float x, y;
}moveup_component_t;

moveup_component_t* moveup_component_new(const char*);
void moveup_component_init(moveup_component_t* c, actor_t*);