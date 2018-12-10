#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <actor.h>
#include <texture.h>
#include <sprite.h>

/* how the render component should be:
* the render component must have just one sprite and one texture but the "drawcall"
* must be done on sprite es: sprite->draw_texture(texture); or sprite->draw_color(sprite, r, g, b, a);
* only the sprite can be drawn onto the screen, the texture must be only a frame buffer with an image
*/

typedef struct render_component{
    component_t component;
    actor_t* owner;
    sprite_t* sprite;
}render_component_t;

void render_component_init(render_component_t*, actor_t* owner, const char* name, int width, int height);

#endif