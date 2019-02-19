#include <actor.h>
#include <utils.h>
#include <stdlib.h>

actor_t* actor_new(const char* name)
{
    actor_t* actor = malloc(sizeof(actor_t));
    CHECK_RET(actor, NULL, "cannot allocate space for actor");
    memset(actor, 0, sizeof(actor_t));

    int len = strlen(name);
    char* buffer = malloc(len + 1);
    strcpy_s(buffer, len + 1, name);
    actor->name = buffer;

    actor->c_head = NULL;
    actor->c_tail = NULL;

    actor->transform.position = vec2_init(0, 0);
    actor->transform.rotation = 0.0f;
    actor->transform.scale = vec2_init(1, 1);

    // SDL_Log("Initialized an actor [%p]", actor);

    return actor;
}

void set_name(actor_t* actor, const char* name)
{
    int len = strlen(name);
    char* buffer = malloc(len + 1);
    strcpy_s(buffer, len + 1, name);
    actor->name = buffer;
}

int add_component(actor_t* actor, component_t* comp)
{
    if(actor->c_head == NULL) //list is empty
    {
        actor->c_head = comp;
        actor->c_tail = comp;
        return 0;
    }

    actor->c_tail->next = comp;
    comp->prev = actor->c_tail;
    actor->c_tail = comp;

    return 0;
}

int get_component(actor_t* actor, const char* c_name, component_t** out_c)
{
    if(actor->c_head == NULL) //list is empty
        return -1;

    component_t* current = actor->c_head;
    while(current)
    {
        if(!strcmp(current->name, c_name)){
            *out_c = current;
            return 0;
        }

        current = current->next;
    }

    return 0;
}

component_t* get_component_by_name(actor_t* actor, const char* c_name)
{
    if(actor->c_head == NULL)
        return NULL;

    component_t* current = actor->c_head;
    while(current)
    {
        if(!strcmp(current->name, c_name))
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}