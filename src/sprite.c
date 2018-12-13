#include <sprite.h>
#include <utils.h>
#include <stdlib.h>

extern ctx_t* ctx;

static void _draw_sprite(sprite_t* sprite)
{
    sprite->rect.x = sprite->position.x;
    sprite->rect.y = sprite->position.y;
    sprite->rect.w = sprite->width * sprite->scale.x;
    sprite->rect.h = sprite->height * sprite->scale.y;

    SDL_RenderCopyEx(ctx->renderer, sprite->texture, NULL, &sprite->rect, sprite->rotation, &sprite->pivot, sprite->flip_flag);
}

static void _draw_sprite_color(sprite_t* sprite, color_t color)
{
    sprite->rect.x = sprite->position.x;
    sprite->rect.y = sprite->position.y;
    sprite->rect.w = sprite->width * sprite->scale.x;
    sprite->rect.h = sprite->height * sprite->scale.y;

    sprite->change_sprite_color(sprite, color);
    SDL_RenderCopyEx(ctx->renderer, sprite->texture, NULL, &sprite->rect, sprite->rotation, &sprite->pivot, sprite->flip_flag);
}

static void _change_sprite_color(sprite_t* sprite, color_t color)
{
    int pitch = 0;
    unsigned char* pixels = NULL;

    if (SDL_LockTexture(sprite->texture, NULL, (void **)&pixels, &pitch)) 
    {
        SDL_Log("unable to lock texture: %s", SDL_GetError());
        return;
    }

    unsigned char colors[4] = { color.r, color.g, color.b, color.a };
    for(int y = 0; y < sprite->width; ++y){
        for(int x = 0; x < sprite->height; ++x){
            memcpy(&pixels[(y * sprite->height + x) * sizeof(color)], colors, sizeof(color));
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
    SDL_RenderCopyEx(ctx->renderer, texture->texture, NULL, &texture->rect, texture->rotation, &texture->pivot, texture->flip_flag);
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
    SDL_RenderCopyEx(ctx->renderer, texture->texture, &texture->src, &texture->rect, texture->rotation, &texture->pivot, texture->flip_flag);
}

static int _flip_x(sprite_t* sprite, uint8_t flip)
{
    if(flip == 0)
    {
        sprite->flip_flag = SDL_FLIP_NONE;
        return 1;
    }
    else if(flip == 1)
    {
        sprite->flip_flag = SDL_FLIP_HORIZONTAL;
        return 0;
    }

    return -1;
}

static int _flip_y(sprite_t* sprite, uint8_t flip)
{
    if(flip == 0)
    {
        sprite->flip_flag = SDL_FLIP_NONE;
        return 1;
    }
    else if(flip == 1)
    {
        sprite->flip_flag = SDL_FLIP_VERTICAL;
        return 0;
    }

    return -1;
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
    sprite->draw_sprite_color = _draw_sprite_color;
    sprite->change_sprite_color = _change_sprite_color;
    sprite->draw_texture = _draw_texture;
    sprite->draw_texture_tiled = _draw_texture_tiled;
    sprite->flip_x = _flip_x;
    sprite->flip_y = _flip_y;

    return sprite;
}