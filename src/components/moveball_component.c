#include <moveball_component.h>
#include <string.h>
#include <stdlib.h>
#include <player.h>
#include <stdio.h>

#define SPEED   0.04
#define OFFSET  0.1

#define ARR_LEN(x)  (sizeof(x) / sizeof((x)[0]))

extern ctx_t* ctx;

static vec2_t directions[4] =
{
    .1f, -.1f, // upright
    -.1f, -.1f, // upleft
    .1f, .1f, // downright
    -.1f, .1f // downleft
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

    // write variables to update x and y
    p->renderer->texture->pos.x = p->pos.x;
    p->renderer->texture->pos.y = p->pos.y;

    if (comp->current_direction.x == directions[0].x && comp->current_direction.y == directions[0].y) //upright
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
        p->renderer->texture->flip_flag = SDL_FLIP_HORIZONTAL;

    p->move_player(p, comp->current_direction);
}

static void _begin(moveball_component_t* comp)
{
    printf("begin play moveball!\n");

    // get the actor once
    comp->player = comp->actor;
    if(!comp->player){
        fprintf(stderr, "actor not available\n");
        // exit(-1);
    }

    comp->current_direction = pick_random_dir();
    // printf("dir: %d\n", comp->current_direction);

    //always disable is started in order to update it only once
    comp->component.started = 1;
}

void moveball_component_init(moveball_component_t* comp, actor_t* actor)
{
    comp->actor = actor;
    comp->component.tick = (void(*)(component_t*))_tick;
    comp->component.begin = (void(*)(component_t*))_begin;
}

moveball_component_t* moveball_component_new(const char* name)
{
    moveball_component_t* comp = malloc(sizeof(moveball_component_t));
    if(!comp) return NULL;

    memset(comp, 0, sizeof(moveball_component_t));
    int len = strlen(name);
    char* buffer = malloc(len + 1);
    strcpy_s(buffer, len + 1, name);
    
    comp->component.name = buffer;
    comp->component.active = 1;

    return comp;
}