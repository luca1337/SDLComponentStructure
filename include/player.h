#ifndef PLAYER_H
#define PLAYER_H

#include <render_component.h>
#include <moveup_component.h>
#include <moveball_component.h>
#include <bounce_component.h>
#include <actor.h>

#include <vec.h>

typedef struct player{
    actor_t actor;
    render_component_t* renderer;
    moveup_component_t* moveup;
    moveball_component_t* moveball;
    bounce_component_t* bounce;
    vec2_t pos;
    int width, height;
    void(*move_player)(struct player*, const vec2_t);
    void(*get_player_pos)(struct player*, vec2_t*);
    void(*get_player_size)(struct player*, int*, int*);
}player_t;

player_t* player_new(vec2_t, const char*, const char*);

#endif
