#include <sprite_component.h>
#include <texture_mgr.h>
#include <string.h>
#include <stdlib.h>
#include <engine_utils.h>

extern ctx_t* ctx;
extern texture_mgr_t* mgr;

static void _tick(sprite_component_t* comp)
{
    // set owner transform
    comp->sprite->position = comp->owner->transform.position;
    comp->sprite->rotation = comp->owner->transform.rotation;
    comp->sprite->scale = comp->owner->transform.scale;

    comp->sprite->draw_texture(comp->sprite);
}

static void _begin(sprite_component_t* comp)
{
    comp->component.started = 1;
}

void sprite_component_init(sprite_component_t* comp, actor_t* owner, const char* name, int width, int height)
{
    comp->owner = owner;
    comp->sprite = sprite_new(width, height);
    texture_t* texture = get_texture(mgr, name);
    comp->sprite->texture = texture->texture;

    comp->component.tick = CastToFuncPtr(_tick, component_t);
    comp->component.begin = CastToFuncPtr(_begin, component_t);
}