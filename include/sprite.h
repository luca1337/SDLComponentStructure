#ifndef SPRITE_H
#define SPRITE_H

#include <gfx.h>
#include <vec.h>
#include <texture.h>

typedef struct sprite{
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect src;
    SDL_Point pivot;
    vec2_t position;
    float rotation;
    vec2_t scale;
    int width, height;
    void(*draw_sprite)(struct sprite* sprite, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void(*change_sprite_color)(struct sprite*, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void(*draw_texture)(struct sprite* surface, texture_t* texture);
    void(*draw_texture_tiled)(struct sprite* sprite, int x_offset, int y_offset, int width, int height);
}sprite_t;

sprite_t* sprite_new(int width, int height);

#endif