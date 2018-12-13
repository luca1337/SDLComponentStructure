#include <sprite.h>
#include <utils.h>
#include <stdlib.h>

extern ctx_t* ctx;

static void _draw_sprite(sprite_t* sprite, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    sprite->rect.x = sprite->position.x;
    sprite->rect.y = sprite->position.y;
    sprite->rect.w = sprite->width * sprite->scale.x;
    sprite->rect.h = sprite->height * sprite->scale.y;

    SDL_RenderCopyEx(ctx->renderer, sprite->texture, NULL, &sprite->rect, sprite->rotation, &sprite->pivot, SDL_FLIP_NONE);
}

static void _change_sprite_color(sprite_t* sprite, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    int pitch = 0;
    unsigned char* pixels = NULL;

    if (SDL_LockTexture(sprite->texture, NULL, (void **)&pixels, &pitch)) 
    {
        SDL_Log("unable to lock texture: %s", SDL_GetError());
        return;
    }

    unsigned char color[4] = { r, g, b, a };
    for(int y = 0; y < sprite->width; ++y){
        for(int x = 0; x < sprite->height; ++x){
            memcpy(&pixels[(y * sprite->height + x) * sizeof(color)], color, sizeof(color));
        }
    }

    SDL_UnlockTexture(sprite->texture);
}

static void _draw_texture(sprite_t* texture)
{
    texture->rect.x = texture->position.x;
    texture->rect.y = texture->position.y;
    texture->rect.w = texture->width * texture->scale.x;
    texture->rect.h = texture->height * texture->scale.y;

    SDL_SetTextureBlendMode(texture->texture, SDL_BLENDMODE_BLEND);
    SDL_RenderCopyEx(ctx->renderer, texture->texture, NULL, &texture->rect, texture->rotation, &texture->pivot, SDL_FLIP_NONE);
}

static void _draw_texture_tiled(sprite_t* texture, int x_offset, int y_offset, int width, int height)
{
    texture->rect.x = texture->position.x;
    texture->rect.y = texture->position.y;
    texture->rect.w = width * texture->scale.x;
    texture->rect.h = height * texture->scale.y;

    texture->src.x = x_offset;
    texture->src.y = y_offset;
    texture->src.w = width;
    texture->src.h = height;

    SDL_SetTextureBlendMode(texture->texture, SDL_BLENDMODE_BLEND);
    SDL_RenderCopyEx(ctx->renderer, texture->texture, &texture->src, &texture->rect, texture->rotation, &texture->pivot, SDL_FLIP_NONE);
}

sprite_t* sprite_new(int width, int height)
{
    sprite_t* sprite = malloc(sizeof(sprite_t));
    CHECK_RET(sprite, NULL, "could not allocate space for sprite")
    memset(sprite, 0, sizeof(sprite_t));

    // create a "texture" from resource with given with and height
    sprite->texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);

    // here i've got a simple empty frame buffer which can be filled with an image or with a color

    sprite->rect.w = width;
    sprite->rect.h = height;

    sprite->width = width;
    sprite->height = height;

    // setup our hooks for draw
    sprite->draw_sprite = _draw_sprite;
    sprite->change_sprite_color = _change_sprite_color;
    sprite->draw_texture = _draw_texture;
    sprite->draw_texture_tiled = _draw_texture_tiled;

    return sprite;
}