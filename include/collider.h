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

typedef struct collider
{
    component_t component;
    actor_t* owner;
    SDL_Rect rect;
    int pad_x,pad_y;
    int width,height;
    vec2_t half;
    vec2_t center;
    vec2_t size;
    uint8_t debug;
    void(*debug_draw_collider)(struct collider* collider);
    vec2_t(*get_center)(struct collider* collider);
    vec2_t(*get_half_size)(struct collider* collider);
    void(*on_collision_enter)(struct collider* collider, struct collider* other);
}collider_t;

void collider_init(collider_t* collider, actor_t* owner, int width, int height);

#endif