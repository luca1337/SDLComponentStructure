#include <collider.h>
#include <engine_utils.h>
#include <gfx.h>

extern ctx_t* ctx;

static void _tick(collider_t* collider)
{
    collider->mesh[0].x = collider->owner->transform.position.x;
    collider->mesh[0].y = collider->owner->transform.position.y;

    collider->mesh[1].x = collider->owner->transform.position.x;
    collider->mesh[1].y = collider->owner->transform.position.y;

    collider->mesh[2].x = collider->owner->transform.position.x + collider->pad_x;
    collider->mesh[2].y = collider->owner->transform.position.y;

    collider->mesh[3].x = collider->owner->transform.position.x;
    collider->mesh[3].y = collider->owner->transform.position.y + collider->pad_y;

    for(unsigned i = 0; i < NUM_OF_RECT; i++)
    {
        SDL_SetRenderDrawColor(ctx->renderer, 0, 255, 255, 255);
        SDL_RenderDrawRect(ctx->renderer, &collider->mesh[i]);
    }
}

void collider_init(collider_t* collider, actor_t* owner, int width, int height)
{
    // get the owner
    collider->owner = owner;

    collider->pad_x = (width * collider->owner->transform.scale.x);
    collider->pad_y = (height * collider->owner->transform.scale.x);

    // first mesh up
    collider->mesh[0].x = collider->owner->transform.position.x;
    collider->mesh[0].y = collider->owner->transform.position.y;
    collider->mesh[0].w = width * collider->owner->transform.scale.x;
    collider->mesh[0].h = 1;

    // second mesh left
    collider->mesh[1].x = collider->owner->transform.position.x;
    collider->mesh[1].y = collider->owner->transform.position.y;
    collider->mesh[1].w = 1;
    collider->mesh[1].h = height * collider->owner->transform.scale.y;

    // third mesh right
    collider->mesh[2].x = collider->owner->transform.position.x + collider->pad_x;
    collider->mesh[2].y = collider->owner->transform.position.y;
    collider->mesh[2].w = 1;
    collider->mesh[2].h = height * collider->owner->transform.scale.y;

    // last mesh down
    collider->mesh[3].x = collider->owner->transform.position.x;
    collider->mesh[3].y = collider->owner->transform.position.y + collider->pad_y;
    collider->mesh[3].w = width * collider->owner->transform.scale.x;   
    collider->mesh[3].h = 1;

    collider->component.tick = CastToFuncPtr(_tick, component_t);
}