#include <utils.h>
#include <engine_utils.h>
#include <texture_mgr.h>
#include <player.h>
#include <enemy.h>
#include <engine.h>
#include <logic.h>
#include <stdlib.h>
#include <sprite.h>
#include <gfx.h>
#include <time.h>
#include <moveball_component.h>

// define all global variables here
ctx_t*                 ctx          = NULL;
engine_t*              engine       = NULL;
texture_mgr_t*         mgr          = NULL;

static player_t*       ball         = NULL;
static player_t*       ball1         = NULL;
static player_t*       ball2         = NULL;
static player_t*       ball3         = NULL;
static enemy_t*        enemy        = NULL;

float timer = 0.0;
int cnt = 0;

static void draw(ctx_t* ctx)
{
    check_collisions(engine);
    engine_tick(engine);
}

static void _init(game_manager_t* gm)
{
    srand(time(NULL));

    //create the context
    ctx = ctx_new("Test", 800, 600, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC, draw);

    //create the engine instance to manage all actors
    engine = engine_new();

    //create the texture manager to manage all textures in memory
    mgr = texture_mrg_new();

    // create entities below and add textures in memory
    add_texture(mgr, "player", "assets/mario2.png", SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 4);
    add_texture(mgr, "tile_sheet", "assets/sheet.png", SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 4);
    add_texture(mgr, "runner", "assets/runner.png", SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 4);

    // create and spawn the player
    vec2_t spawn_pos = vec2_init(ctx->width / 2, ctx->height / 2);
    ball = player_new(spawn_pos, "player", "runner", 0, 0);
    spawn_actor(engine, CastToActor(ball));

    vec2_t spawn_pos1 = vec2_init(ctx->width / 2, ctx->height / 2 - 64);
    ball1 = player_new(spawn_pos1, "player", "runner", 0, 0);
    spawn_actor(engine, CastToActor(ball1));

    vec2_t spawn_pos2 = vec2_init(ctx->width / 2, ctx->height / 2 - 128);
    ball2 = player_new(spawn_pos2, "player", "runner", 0, 0);
    spawn_actor(engine, CastToActor(ball2));

    vec2_t spawn_pos3 = vec2_init(ctx->width / 2, ctx->height / 2 - 195);
    ball3 = player_new(spawn_pos3, "player", "runner", 0, 1);
    spawn_actor(engine, CastToActor(ball3));

}

static void _tick(game_manager_t* gm)
{
    while(ctx->is_running)
    {
        ctx_update(ctx);
    }

    // clean up everything
    engine_destroy(engine);
    destroy_texture_mgr(mgr);
    ctx_destroy(ctx);
}


game_manager_t* game_manager_new()
{
    game_manager_t* game_manager = malloc(sizeof(game_manager_t));
    CHECK_RET(game_manager, NULL, "could not create game_manager structure..")

    memset(game_manager, 0, sizeof(game_manager_t));

    game_manager->init = _init;
    game_manager->tick = _tick;

    return game_manager;
}