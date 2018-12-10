#include <texture.h>
#include <string.h>
#include <utils.h>
#include <stdlib.h>

#include <stb_image.h>
#include <SDL.h>

#include <gfx.h>

extern ctx_t* ctx;

texture_t* texture_new(const char* file_path)
{
    texture_t* texture = malloc(sizeof(texture_t));
    CHECK_RET(texture, NULL, "could not allocate space for texture.")
    memset(texture, 0, sizeof(texture_t));

    int width, height, color_channel;
    unsigned char* data = stbi_load(file_path, &width, &height, &color_channel, 4);

    texture->texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_LOG(texture->texture, NULL);

    int pitch = 0;
    unsigned char* pixel = NULL;

    if (SDL_LockTexture(texture->texture, NULL, (void **)&pixel, &pitch))
    {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
        return NULL;
    }

    memset(pixel, 0, width * height * color_channel);
    memcpy(pixel, data, width * height * color_channel);
    SDL_UnlockTexture(texture->texture);

    texture->width = width;
    texture->height = height;

    return texture;
}