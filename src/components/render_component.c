#include <render_component.h>
#include <texture_mgr.h>
#include <string.h>
#include <stdlib.h>

extern ctx_t* ctx;
extern texture_mgr_t* mgr;

static void tick(render_component_t* c)
{
    // wat else ?
    if(c->texture) // i'm not gonna crash
    {
        c->texture->draw_tex(c->texture);
    }
    else
    {
        c->sprite->draw_sprite(c->sprite, 255, 0, 0, 255);
    }
}

render_component_t* render_component_new(const char* name)
{
    render_component_t* comp = (render_component_t*)component_new(name, GET_SIZE(render_component_t));

    return comp;
}

void render_component_init(render_component_t* c, const char* name, int sprite_mode, int width, int height, int pivot)
{
    // i don't like this shit
    if(sprite_mode == 0)
    {
        c->texture = get_texture(mgr, name);
    }
    else if(sprite_mode == 1)
    {
        c->sprite = sprite_new(width, height, pivot);
    }

    c->component.tick = (void(*)(component_t*))tick;
}