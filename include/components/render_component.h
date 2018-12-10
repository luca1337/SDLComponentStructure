#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <actor.h>
#include <texture.h>
#include <sprite.h>

typedef struct render_component{
    component_t component;
    actor_t* owner;
    texture_t* texture;
    sprite_t* sprite;
}render_component_t;

void render_component_init(render_component_t*, actor_t* owner, const char* name, int sprite_mode, int width, int height, int pivot);

#endif