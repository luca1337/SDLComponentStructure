#ifndef QUAD_RENDERER_COMPONENT_H
#define QUAD_RENDERER_COMPONENT_H

#include <component.h>
#include <sprite.h>
#include <engine_utils.h>

typedef struct quad_renderer{
    component_t component;
    actor_t* owner;
    sprite_t* sprite;
}quad_renderer_t;

void quad_renderer_init(quad_renderer_t* quad_renderer, actor_t* owner, int width, int height);

#endif