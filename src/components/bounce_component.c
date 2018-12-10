#include <bounce_component.h>
#include <string.h>
#include <stdlib.h>
#include <player.h>
#include <stdio.h>

extern ctx_t* ctx;

static void _tick(bounce_component_t* comp)
{
    player_t* player = (player_t*)comp->player;

    if(!player) return;

    //change direction based on collision map part

    if(player->pos.x + player->width > ctx->width)
    {
        vec2_t ref = vec2_reflected(comp->moveball_ref->current_direction, vec2_init(-1, 0));
        comp->moveball_ref->current_direction = ref;
    }

    if(player->pos.y < 0)
    {
        vec2_t ref = vec2_reflected(comp->moveball_ref->current_direction, vec2_init(0, 1));
        comp->moveball_ref->current_direction = ref;
    }

    if(player->pos.x < 0)
    {
        vec2_t ref = vec2_reflected(comp->moveball_ref->current_direction, vec2_init(1, 0));
        comp->moveball_ref->current_direction = ref;
    }

    if(player->pos.y + player->width > ctx->height)
    {
        vec2_t ref = vec2_reflected(comp->moveball_ref->current_direction, vec2_init(0, -1));
        comp->moveball_ref->current_direction = ref;
    }
}

static void _begin(bounce_component_t* comp)
{
    // get the actor only once not each frame
    comp->player = (player_t*)comp->actor;
    if(!comp->player)
    {
        fprintf(stderr, "could not get actor reference.\n");
        return;
    }

    // get it's component
    get_component(comp->actor, "moveball_component", (component_t**)&comp->moveball_ref);
    if(!comp->moveball_ref)
    {
        fprintf(stderr, "could not get_component\n");
        return;
    }

    comp->component.started = 1;
}

void bounce_component_init(bounce_component_t* comp, actor_t* actor)
{
    comp->actor = actor;
    comp->component.tick = (void(*)(component_t*))_tick;
    comp->component.begin = (void(*)(component_t*))_begin;
}