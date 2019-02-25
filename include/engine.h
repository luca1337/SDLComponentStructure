#ifndef ENGINE_H
#define ENGINE_H

#include <actor.h>
#include <dynamic_array.h>

typedef struct engine{
    actor_t* head;
    actor_t* tail;
    unsigned int actor_count;
    dynamic_array_t* collision_pairs;
}engine_t;

engine_t* engine_new();
int spawn_actor(engine_t* engine, actor_t* actor);
int engine_tick(engine_t*);
void engine_destroy(engine_t*);
void check_collisions(engine_t* engine);

#endif