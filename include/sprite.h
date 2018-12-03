#ifndef SPRITE_H
#define SPRITE_H

#include <gfx.h>
#include <vec.h>

typedef struct sprite{
    SDL_Texture* tex;
    SDL_Rect rect;
    SDL_Point pivot;
    double degrees;
    vec2_t pos;
    int width,height;
    void(*draw_sprite)(struct sprite*, uint8_t, uint8_t, uint8_t, uint8_t);
    void(*change_sprite_color)(struct sprite*, uint8_t, uint8_t, uint8_t, uint8_t);
}sprite_t;

sprite_t* sprite_new(int, int, int);

#endif