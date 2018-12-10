#ifndef ENEMY_H
#define ENEMY_H

#include <animation_component.h>
#include <actor.h>
#include <vec.h>

typedef struct enemy{
    actor_t actor;
    animation_component_t* animation_renderer;
}enemy_t;

enemy_t* enemy_new(vec2_t pos, const char*);

#endif