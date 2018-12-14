#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <utils.h>
#include <gfx.h>
#include <stb_image.h>

ctx_t* ctx_new(const char* title, int width, int height, unsigned flags, void(*_post_hook_draw)(ctx_t* ctx))
{
    ctx_t* ctx = malloc(sizeof(ctx_t));
    CHECK_RET(ctx, NULL, "could not create context")

    memset(ctx, 0, sizeof(ctx_t));

    SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);

    ctx->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    if(!ctx->window)
    {
        fprintf(stderr, "Could not create SDL window, error: %s\n", SDL_GetError());
        return NULL;
    }

    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, flags);
    if(!ctx->renderer)
    {
        fprintf(stderr, "Could not create SDL renderer, error: %s\n", SDL_GetError());
        return NULL;
    }

    ctx->width = width;
    ctx->height = height;

    ctx->start = SDL_GetPerformanceCounter();
    ctx->key_state = SDL_GetKeyboardState(NULL);
    ctx->h_width = ctx->width / 2;
    ctx->h_height = ctx->height / 2;
    ctx->screen_ratio = (float)ctx->width / (float)ctx->height;
    ctx->delta_seconds = 0;
    ctx->is_running = 1;
    ctx->post_hook_draw = _post_hook_draw;

    return ctx;
}


void ctx_update(ctx_t* ctx)
{
    // update event queue and internal input device state
    SDL_PumpEvents();

    // clear color
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);

    SDL_SetRenderDrawBlendMode(ctx->renderer, SDL_BLENDMODE_BLEND);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            ctx->is_running = 0;
        }
    }

    // draw logic here
    ctx->post_hook_draw(ctx);

    ctx->end = SDL_GetPerformanceCounter();
    ctx->delta_seconds = (ctx->end - ctx->start) / (double)SDL_GetPerformanceFrequency();
    ctx->start = ctx->end;

    // render present scene in the back buffer
    SDL_RenderPresent(ctx->renderer);
}

uint8_t get_key(ctx_t* ctx, SDL_Scancode key)
{
    return ctx->key_state[key];
}

void ctx_destroy(ctx_t* ctx)
{
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
}