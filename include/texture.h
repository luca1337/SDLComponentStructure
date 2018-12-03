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
    SDL_Point pivot;
    SDL_RendererFlip flip_flag;
    char* name;
    int id;
    int width, height;
    double degrees;
    vec2_t pos;
    void(*draw_tex)(struct texture*);
}texture_t;

texture_t* texture_new(const char*);

#endif