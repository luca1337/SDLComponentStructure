#include <sprite.h>
#include <utils.h>
#include <stdlib.h>

extern ctx_t* ctx;

#define MEMCPY_TEXTURE(w, h, data, color_arr){\
    for(int y = 0; y < h; ++y){\
        for(int x = 0; x < w; ++x){\
            memcpy(&data[(y * h + x) * sizeof(color_arr)], color_arr, sizeof(color_arr));\
        }\
    }\
}\

static void _draw_sprite(struct sprite* s, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    s->rect.x = s->pos.x;
    s->rect.y = s->pos.y;
    s->rect.w = s->width;
    s->rect.h = s->height;

    SDL_RenderCopyEx(ctx->renderer, s->tex, NULL, &s->rect, s->degrees, &s->pivot, SDL_FLIP_NONE);
}

static void _change_sprite_color(struct sprite* sprite, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    int pitch = 0;
    unsigned char* pixels = NULL;

    if (SDL_LockTexture(sprite->tex, NULL, (void **)&pixels, &pitch)) {
        SDL_Log("Unable to lock texture: %s\n", SDL_GetError());
        return;
    }

    unsigned char color[4] = { r, g, b, a };
    MEMCPY_TEXTURE(sprite->width, sprite->height, pixels, color)

    SDL_UnlockTexture(sprite->tex);
}

sprite_t* sprite_new(int width, int height, int centered_pivot)
{
    sprite_t* sprite = malloc(sizeof(sprite_t));
    CHECK_RET(sprite, NULL, "could not allocate space for sprite")
    memset(sprite, 0, sizeof(sprite_t));

    sprite->tex = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);

    int pitch = 0;
    unsigned char* pixels = NULL;

    if (SDL_LockTexture(sprite->tex, NULL, (void **)&pixels, &pitch))
    {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
        return NULL;
    }

    unsigned char color[4] = { 255, 0, 0, 255 };
    for(int y = 0; y < width; ++y){
        for(int x = 0; x < height; ++x){
            memcpy(&pixels[(y * height + x) * sizeof(color)], color, sizeof(color));
        }
    }

    SDL_UnlockTexture(sprite->tex);

    sprite->rect.w = width;
    sprite->rect.h = height;

    sprite->width = sprite->rect.w;
    sprite->height = sprite->rect.h;

    if(centered_pivot == 1)
    {
        sprite->pivot.x = sprite->width / 2;
        sprite->pivot.y = sprite->width / 2;
    }

    sprite->degrees = 0;

    sprite->draw_sprite = _draw_sprite;
    sprite->change_sprite_color = _change_sprite_color;

    return sprite;
}