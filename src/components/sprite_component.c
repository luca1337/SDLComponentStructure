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

    if(comp->can_mov)
    {
        // try to move it
        if(get_key(ctx, SDL_SCANCODE_D))
            comp->owner->transform.position.x += 150 * ctx->delta_seconds;

        if(get_key(ctx, SDL_SCANCODE_A))
            comp->owner->transform.position.x += -150 * ctx->delta_seconds;

        if(get_key(ctx, SDL_SCANCODE_W))
            comp->owner->transform.position.y += -150 * ctx->delta_seconds;

        if(get_key(ctx, SDL_SCANCODE_S))
            comp->owner->transform.position.y += 150 * ctx->delta_seconds;
    }

    comp->owner->transform.rotation += 150.0f * ctx->delta_seconds;

    comp->sprite->draw_texture(comp->sprite);
}

static void _begin(sprite_component_t* comp)
{
    comp->component.started = 1;
}

void sprite_component_init(sprite_component_t* comp, actor_t* owner, const char* texture_name, int width, int height, char can_mov)
{
    comp->owner = owner;
    comp->can_mov = can_mov;

    texture_t* tex = get_texture(mgr, texture_name);
    comp->sprite = sprite_new(width, height);
    comp->sprite->texture = tex->texture;

    comp->sprite->pivot.x = (comp->sprite->width * comp->owner->transform.scale.x) / 2;
    comp->sprite->pivot.y = (comp->sprite->height * comp->owner->transform.scale.y) / 2;

    comp->component.tick = CastToFuncPtr(_tick, component_t);
    comp->component.begin = CastToFuncPtr(_begin, component_t);
}