#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H

#include <actor.h>
#include <player.h>
#include <moveball_component.h>
#include <vec.h>

typedef struct move_component{
    component_t component;
    actor_t* owner;
    void* paddle;
    moveball_component_t* moveball_ref;
    player_t* ball;
    char side_paddle;
    char auto_move;
}move_component_t;

move_component_t* move_component_new(const char*);
void move_component_init(move_component_t*, actor_t*, player_t*, char, char);

#endif