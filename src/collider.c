#include <collider.h>
#include <engine_utils.h>
#include <gfx.h>

extern ctx_t* ctx;

static void _tick(collider_t* collider)
{
    collider->rect.x = collider->owner->transform.position.x;
    collider->rect.y = collider->owner->transform.position.y;

    if(collider->debug == 1)
    {
        SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(ctx->renderer, &collider->rect);
    }
}

static void _begin(collider_t* comp)
{

    comp->component.started = 1;
}

static vec2_t _get_center(collider_t* collider)
{
    vec2_t result;
    result.x = collider->owner->transform.position.x + collider->get_half_size(collider).x;
    result.y = collider->owner->transform.position.y + collider->get_half_size(collider).y;
    return result;
}

static vec2_t _get_half_size(collider_t* collider)
{
    return vec2_init((collider->rect.w) * 0.5f, (collider->rect.h) * 0.5f);
}

void collider_init(collider_t* collider, actor_t* owner, int width, int height)
{
    // get the owner
    collider->owner = owner;

    collider->size.x = (int)(width * collider->owner->transform.scale.x);
    collider->size.y = (int)(height * collider->owner->transform.scale.y);

    collider->rect.x = collider->owner->transform.position.x;
    collider->rect.y = collider->owner->transform.position.y;
    collider->rect.w = width * collider->owner->transform.scale.x;
    collider->rect.h = height * collider->owner->transform.scale.y;

    collider->get_center = _get_center;
    collider->get_half_size = _get_half_size;

    collider->component.tick = CastToFuncPtr(_tick, component_t);
    collider->component.begin = CastToFuncPtr(_begin, component_t);
}