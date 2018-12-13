#ifndef SPRITE_H
#define SPRITE_H

#include <gfx.h>
#include <vec.h>
#include <texture.h>
#include <color.h>

typedef struct sprite{
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect src;
    SDL_Point pivot;
    SDL_RendererFlip flip_flag;
    vec2_t position;
    float rotation;
    vec2_t scale;
    int width, height;
    void(*draw_sprite)(struct sprite* sprite);
    void(*draw_sprite_color)(struct sprite* sprite, color_t color);
    void(*change_sprite_color)(struct sprite*, color_t color);
    void(*draw_texture)(struct sprite* texture);
    void(*draw_texture_tiled)(struct sprite* texture, int x_offset, int y_offset, int width, int height);
    int(*flip_x)(struct sprite* sprite, uint8_t flip);
    int(*flip_y)(struct sprite* sprite, uint8_t flip);
}sprite_t;

sprite_t* sprite_new(int width, int height);

#endif