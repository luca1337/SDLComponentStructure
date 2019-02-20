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
#include <palette.h>
#include <time.h>
#include <moveball_component.h>

// define all global variables here
ctx_t*                 ctx          = NULL;
engine_t*              engine       = NULL;
texture_mgr_t*         mgr          = NULL;

static palette_t*      paddles[2];
static player_t*       ball         = NULL;
static player_t*       ball2         = NULL;
static player_t*       ball3         = NULL;
static player_t*       ball4         = NULL;
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
    vec2_t spawn_pos = vec2_init(ctx->width / 2 - 64, ctx->height / 2 - 64);
    ball = player_new(spawn_pos, "player", "runner", 1, 1);
    spawn_actor(engine, CastToActor(ball), "mario");

    vec2_t spawn_pos4 = vec2_init(ctx->width / 2 - 64, ctx->height / 2 + 70);
    ball4 = player_new(spawn_pos4, "player", "runner", 1, 0);
    spawn_actor(engine, CastToActor(ball4), "mario3");

    vec2_t spawn_pos2 = vec2_init(ctx->width / 2 - 64, ctx->height / 2 - 256);
    ball2 = player_new(spawn_pos2, "player", "runner2", 1, 0);
    spawn_actor(engine, CastToActor(ball2), "mario1");

    // paddle 01
    /*vec2_t paddle01_pos = vec2_init(10, ctx->height / 2 - 100);
    vec2_t paddle01_size = vec2_init(20, 100);
    paddles[0] = palette_new(paddle01_pos, paddle01_size, ball, "paddle01", 0, 0);
    spawn_actor(engine, CastToActor(paddles[0]));

    //paddle 02
    vec2_t paddle02_pos = vec2_init( (ctx->width - 20) - 10, ctx->height / 2 - 100);
    vec2_t paddle02_size = vec2_init(20, 100);
    paddles[1] = palette_new(paddle02_pos, paddle02_size, ball, "paddle02", 1, 1);
    spawn_actor(engine, CastToActor(paddles[1]));*/

    vec2_t enemy_pos = vec2_init( (ctx->width / 2) - 65, ctx->height / 2 + 125);
    enemy = enemy_new(enemy_pos, "runner");
    spawn_actor(engine, CastToActor(enemy), "runner");
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