#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <gfx.h>
#include <vec.h>

typedef struct texture{
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect src;
    SDL_Point pivot;
    SDL_RendererFlip flip_flag;
    char* name;
    int id;
    int width, height;
    vec2_t position;
    float rotation;
    vec2_t scale;
    void(*draw_tex)(struct texture* texture);
    void(*draw_tex_tiled)(struct texture* texture, int x_index, int y_index, int width, int height);
}texture_t;

texture_t* texture_new(const char* name);

#endif