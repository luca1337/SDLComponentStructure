#include <engine.h>

#include <utils.h>
#include <stdlib.h>

engine_t* engine_new()
{
    engine_t* engine = malloc(sizeof(engine_t));
    CHECK_RET(engine, NULL, "could not allocate space for engine initialization..")
    memset(engine, 0, sizeof(engine_t));
    return engine;
}

int spawn_actor(engine_t* e, actor_t* actor)
{
    if(e->head == NULL) //list first element?
    {
        e->head = actor;
        e->tail = actor;
        printf("first add!\n");
    }
    else
    {
        e->tail->next = actor;
        actor->prev = e->tail;
        e->tail = actor;
        printf("second add!\n");
    }
    return 0;
}


int tick_actors(engine_t* e)
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
                continue;

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