#include <engine.h>

#include <utils.h>
#include <stdlib.h>
#include <physics.h>
#include <SDL.h>

engine_t* engine_new()
{
    engine_t* engine = malloc(sizeof(engine_t));
    CHECK_RET(engine, NULL, "could not allocate space for engine initialization..")
    memset(engine, 0, sizeof(engine_t));

    engine->collision_pairs = dynamic_array_new(4, NULL);

    return engine;
}

int spawn_actor(engine_t* e, actor_t* actor)
{
    if(e->head == NULL)
    {
        e->head = actor;
        e->tail = actor;
        e->actor_count++;
        dynamic_array_insert(e->collision_pairs, (void*)actor);
    }
    else
    {
        e->tail->next = actor;
        actor->prev = e->tail;
        e->tail = actor;
        e->actor_count++;
        dynamic_array_insert(e->collision_pairs, (void*)actor);
    }
    return 0;
}

void check_collisions(engine_t* engine)
{
    for (int i = 0; i < engine->actor_count - 1; i++)
    {
        collider_t* a = (collider_t*)get_component_by_name((actor_t*)engine->collision_pairs->data[i], "collider");

        for (int j = i + 1; j < engine->actor_count; j++)
        {
            collider_t* b = (collider_t*)get_component_by_name((actor_t*)engine->collision_pairs->data[j], "collider");

            if(intersect(a, b))
            {
                SDL_Log("%s collided with %s", a->owner->name, b->owner->name);
            }
        }
    }
}

int engine_tick(engine_t* e)
{
    actor_t* actor = e->head;
    while(actor)
    {
        component_t* c = actor->c_head;
        while(c)
        {
            if(c->active == 0) {
                c = c->next;
                continue;
            }

            if(c->started == 0 && c->begin)
                c->begin(c);

            if(!c->tick)
                c = c->next;

            c->tick(c);
            
            c = c->next;
        }

        actor = actor->next;
    }
    return 0;
}

void engine_destroy(engine_t* engine)
{
    actor_t* actor = engine->head;
    while(actor)
    {
        component_t* comp = actor->c_head;
        while(comp)
        {
            component_t* next = comp->next;
            free(comp);
            comp = NULL;
            comp = next;
        }
        actor_t* next = actor->next;
        free(actor);
        actor = NULL;
        actor = next;
    }
}