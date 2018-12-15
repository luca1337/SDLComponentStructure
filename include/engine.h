#ifndef ENGINE_H
#define ENGINE_H

#include <actor.h>

typedef struct engine{
    actor_t* head;
    actor_t* tail;
}engine_t;

engine_t* engine_new();
int spawn_actor(engine_t*, actor_t*);
int engine_tick(engine_t*);
void engine_destroy(engine_t*);

#endif