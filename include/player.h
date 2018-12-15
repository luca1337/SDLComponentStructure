#ifndef PLAYER_H
#define PLAYER_H

#include <sprite_component.h>
#include <moveball_component.h>
#include <bounce_component.h>
#include <animation_component.h>
#include <quad_renderer_component.h>
#include <rigid_body.h>
#include <collider.h>
#include <transform.h>
#include <actor.h>

#include <vec.h>

typedef struct player{
    actor_t actor;
    sprite_component_t* renderer;
    animation_component_t* animation;
    moveball_component_t* moveball;
    bounce_component_t* bounce;
    quad_renderer_t* quad;
    collider_t* collider;
    rigid_body_t* rb;
    void(*move_player)(struct player*, const vec2_t);
    void(*get_player_pos)(struct player*, vec2_t*);
    void(*get_player_size)(struct player*, int*, int*);
}player_t;

player_t* player_new(vec2_t, const char*, const char*);

#endif
