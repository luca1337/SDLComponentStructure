#ifndef COLLIDER_H
#define COLLIDER_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <actor.h>
#include <vec.h>
#include <transform.h>

#define NUM_OF_RECT 4

typedef struct collider{
    component_t component;
    actor_t* owner;
    SDL_Rect rect;
    int pad_x,pad_y;
    int width,height;
    vec2_t half;
    vec2_t center;
    uint8_t debug;
    void(*debug_draw_collider)(struct collider* collider);
}collider_t;

void collider_init(collider_t* collider, actor_t* owner, int width, int height);

#endif