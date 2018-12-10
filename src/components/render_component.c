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
        c->texture->position = c->owner->transform.position;
        c->texture->rotation = c->owner->transform.rotation;
        c->texture->scale = c->owner->transform.scale;
        c->texture->draw_tex(c->texture);
    }
    else
    {
        c->sprite->position = c->owner->transform.position;
        c->sprite->rotation = c->owner->transform.rotation;
        c->sprite->scale = c->owner->transform.scale;
        c->sprite->draw_sprite(c->sprite, 255, 0, 0, 255);
    }
}

void render_component_init(render_component_t* c, actor_t* owner, const char* name, int sprite_mode, int width, int height, int pivot)
{
    c->owner = owner;

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