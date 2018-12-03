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
    p->pos.x += dir.x;
    p->pos.y += dir.y;
}

static void get_player_pos(player_t* p, vec2_t* v_out)
{
    v_out->x = p->pos.x;
    v_out->y = p->pos.y;
}

static void get_player_size(player_t* p, int* x, int* y)
{
    *x = p->renderer->texture->width;
    *y = p->renderer->texture->height;
}

player_t* player_new(vec2_t spawn_pos, const char* actor_name, const char* tex_path)
{
    // crate player 
    player_t* player = malloc(sizeof(player_t));
    CHECK_RET(player, NULL, "could not allocate space for player struct\n");
    memset(player, 0, sizeof(player_t));

    //setup renderer component
    player->renderer = render_component_new("visualizer");
    render_component_init(player->renderer, actor_name, 0, 0, 0, 0);
    add_component(&player->actor, CastToComponent(player->renderer));

    //setup move component
    player->moveball = moveball_component_new("ballmover");
    moveball_component_init(player->moveball, CastToActor(player));
    add_component(&player->actor, CastToComponent(player->moveball));

    // //setup bounce component
    player->bounce = bounce_component_new("bounce");
    bounce_component_init(player->bounce, CastToActor(player));
    add_component(&player->actor, CastToComponent(player->bounce));

    player->renderer->texture->pos.x = spawn_pos.x;
    player->renderer->texture->pos.y = spawn_pos.y;

    player->pos.x = spawn_pos.x;
    player->pos.y = spawn_pos.y;

    player->width = player->renderer->texture->width;
    player->height = player->renderer->texture->height;

    player->move_player = move_player;
    player->get_player_pos = get_player_pos;
    player->get_player_size = get_player_size;

    return player;
}