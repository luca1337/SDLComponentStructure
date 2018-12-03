#ifndef ENEMY_H
#define ENEMY_H

#include <render_component.h>
#include <moveup_component.h>
#include <actor.h>
#include <vec.h>

typedef struct enemy{
    actor_t actor;
    render_component_t* renderer;
    vec2_t pos;
    int width, height;
}enemy_t;

enemy_t* enemy_new(float, float, const char*);

#endif