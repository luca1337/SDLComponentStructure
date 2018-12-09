#include <moveup_component.h>

#include <gfx.h>

#include <player.h>

#include <stdlib.h>
#include <string.h>
#include <vec.h>

extern ctx_t* ctx;

#define SPEED   0.4
#define OFFSET  0.1

static float    accumulator     = 0.0f;

static vec2_t   right           = { SPEED, 0 };
static vec2_t   left            = { -SPEED, 0 };
static vec2_t   up              = { 0, -SPEED };
static vec2_t   down            = { 0, SPEED };

static void update_input(moveup_component_t* c)
{
    player_t* p = (player_t*)c->actor;

    if(!p) return;

    // write variables to update x and y
    p->renderer->texture->pos.x = p->pos.x;
    p->renderer->texture->pos.y = p->pos.y;

    // printf("pos_x: [%.2f], pos_y: [%.2f]\n", p->pos.x, p->pos.y);

    if(get_key(ctx, SDL_SCANCODE_D) && p->pos.x + p->width < ctx->width)
        p->move_player(p, right);

    if(get_key(ctx, SDL_SCANCODE_A) && p->pos.x > 0)
        p->move_player(p, left);

    if(get_key(ctx, SDL_SCANCODE_W) && p->pos.y > 0)
        p->move_player(p, up);
        
    if(get_key(ctx, SDL_SCANCODE_S) && p->pos.y + p->height < ctx->height)
        p->move_player(p, down);
}

static void tick(moveup_component_t* c)
{
    update_input(c);
}

void moveup_component_init(moveup_component_t* c, actor_t* actor)
{
    c->actor = actor;
    c->component.tick = (void(*)(component_t*))tick;
}

moveup_component_t* moveup_component_new(const char* name)
{
    moveup_component_t* comp = (moveup_component_t*)component_new(name, GET_SIZE(moveup_component_t));

    return comp;
}