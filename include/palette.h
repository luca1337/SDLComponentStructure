#ifndef PALETTE_H
#define PALETTE_H

#include <actor.h>
#include <vec.h>
#include <sprite.h>

#include <sprite_component.h>
#include <move_component.h>

typedef struct palette{
    actor_t actor;
    vec2_t position;
    int width, height;
    sprite_component_t* sprite_component;
    move_component_t* move_component;
}palette_t;

palette_t* palette_new(vec2_t, vec2_t, player_t*, const char* name, char, char);

#endif