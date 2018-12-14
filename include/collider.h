#ifndef COLLIDER_H
#define COLLIDER_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <actor.h>

#define NUM_OF_RECT 4

typedef struct collider{
    component_t component;
    actor_t* owner;
    SDL_Rect mesh[NUM_OF_RECT];
    int pad_x,pad_y;
    void(*debug_draw_collider)(struct collider* collider);
}collider_t;

void collider_init(collider_t* collider, actor_t* owner, int width, int height);

#endif