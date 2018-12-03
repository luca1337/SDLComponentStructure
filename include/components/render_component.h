#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <component.h>
#include <texture.h>
#include <sprite.h>

typedef struct render_component{
    component_t component;
    texture_t* texture;
    sprite_t* sprite;
}render_component_t;

render_component_t* render_component_new(const char*);
void render_component_init(render_component_t*, const char*, int, int, int, int);

#endif