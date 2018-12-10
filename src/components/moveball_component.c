#include <moveball_component.h>
#include <string.h>
#include <stdlib.h>
#include <player.h>
#include <stdio.h>
#include <engine_utils.h>

#define OFFSET  0.1

#define ARR_LEN(x)  (sizeof(x) / sizeof((x)[0]))

extern ctx_t* ctx;
#define SPEED 500

static vec2_t directions[4] =
{
    SPEED, -SPEED, // upright
    -SPEED, -SPEED, // upleft
    SPEED, SPEED, // downright
    -SPEED, SPEED // downleft
};

static vec2_t pick_random_dir()
{
    int rnd = rand() % ARR_LEN(directions);
    return directions[rnd];
}

static void _tick(moveball_component_t* comp)
{
    player_t* p = (player_t*)comp->player;

    if(!p) return;
    
    /*if (comp->current_direction.x == directions[0].x && comp->current_direction.y == directions[0].y) //upright
        // flip none
        p->renderer->texture->flip_flag = SDL_FLIP_NONE;
    else if (comp->current_direction.x == directions[1].x && comp->current_direction.y == directions[1].y)
        // flip left
        p->renderer->texture->flip_flag = SDL_FLIP_HORIZONTAL;
    else if (comp->current_direction.x == directions[2].x && comp->current_direction.y == directions[2].y)
        // flip left
        p->renderer->texture->flip_flag = SDL_FLIP_NONE;
    else if (comp->current_direction.x == directions[3].x && comp->current_direction.y == directions[3].y)
        // flip none
        p->renderer->texture->flip_flag = SDL_FLIP_HORIZONTAL;*/

    p->move_player(p, comp->current_direction);
}

static void _begin(moveball_component_t* comp)
{
    // get the actor once
    comp->player = comp->actor;
    if(!comp->player){
        fprintf(stderr, "actor not available\n");
        // exit(-1);
    }

    comp->current_direction = pick_random_dir();

    //always disable is started in order to update it only once
    comp->component.started = 1;
}

void moveball_component_init(moveball_component_t* comp, actor_t* actor)
{
    comp->actor = actor;
    comp->component.tick = CastToFuncPtr(_tick, component_t);
    comp->component.begin = CastToFuncPtr(_begin, component_t);
}