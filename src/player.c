#include <stdlib.h>

#include <player.h>
#include <utils.h>

#include <texture_mgr.h>
#include <engine.h>

#include <engine_utils.h>

extern ctx_t* ctx;
extern texture_mgr_t* mgr;
extern engine_t* engine;

static void move_player(player_t* p, const vec2_t dir)
{
    p->actor.transform.position.x += dir.x * ctx->delta_seconds;
    p->actor.transform.position.y += dir.y * ctx->delta_seconds;
}

static void get_player_pos(player_t* p, vec2_t* v_out)
{
    v_out->x = p->actor.transform.position.x;
    v_out->y = p->actor.transform.position.y;
}

static void get_player_size(player_t* p, int* x, int* y)
{
    *x = p->actor.transform.scale.x;
    *y = p->actor.transform.scale.y;
}

player_t* player_new(vec2_t spawn_pos, const char* actor_name, const char* tex_path, char gravity, char can_mov)
{
    // crate player 
    player_t* player = malloc(sizeof(player_t));
    CHECK_RET(player, NULL, "could not allocate space for player struct\n");
    memset(player, 0, sizeof(player_t));

    // initialize it's transform
    player->actor.transform.position = vec2_init(spawn_pos.x, spawn_pos.y);
    player->actor.transform.rotation = 0;
    player->actor.transform.scale = vec2_init(2, 2);

    //setup renderer component
    player->renderer = COMPONENT_NEW(sprite_component, sprite_component_t);
    sprite_component_init(player->renderer, &player->actor, actor_name, 32, 32, can_mov);
    add_component(&player->actor, CastToComponent(player->renderer));

    //quad component
    /*player->quad = COMPONENT_NEW(quad_renderer, quad_renderer_t);
    quad_renderer_init(player->quad, &player->actor, 45, 20);
    add_component(&player->actor, CastToComponent(player->quad));*/

    //collider component
    player->collider = COMPONENT_NEW(collider, collider_t);
    collider_init(player->collider, &player->actor, player->renderer->sprite->width, player->renderer->sprite->height);
    add_component(&player->actor, CastToComponent(player->collider));
    player->collider->debug = 1;

    SDL_Log("player center_x: [%.2f] player center_y [%.2f]", player->collider->get_center(player->collider).x, player->collider->get_center(player->collider).y);

    //rigid bodyyy
    player->rb = COMPONENT_NEW(rigid_body, rigid_body_t);
    rigid_body_init(player->rb, &player->actor, gravity);
    add_component(&player->actor, CastToComponent(player->rb));

    /*//setup move component
    player->moveball = COMPONENT_NEW(moveball_component, moveball_component_t);
    moveball_component_init(player->moveball, CastToActor(player));
    add_component(&player->actor, CastToComponent(player->moveball));

    //setup bounce component
    player->bounce = COMPONENT_NEW(bounce_component, bounce_component_t);
    bounce_component_init(player->bounce, CastToActor(player));
    add_component(&player->actor, CastToComponent(player->bounce));*/

    // hook our function pointers
    player->move_player = move_player;
    player->get_player_pos = get_player_pos;
    player->get_player_size = get_player_size;

    return player;
}