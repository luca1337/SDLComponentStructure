#ifndef COMPONENT_H
#define COMPONENT_H

#define GET_SIZE(x) sizeof(x)

#define COMPONENT_NEW(type, cast) (cast*)component_new(#type, sizeof(type ##_t))

#include <utils.h>
#include <stdlib.h>
#include <SDL.h>

typedef struct component{
    struct component* next;
    struct component* prev;
    char* name;
    char started, active;
    void(*tick)(struct component* comp);
    void(*begin)(struct component* comp);
    void(*destroy)(struct component* comp);
    void(*set_name)(struct component*, const char* new_name);
}component_t;

static void _set_name(component_t* comp, const char* name)
{
    int len = strlen(name);
    char* buffer = malloc(len + 1);
    strcpy_s(buffer, len + 1, name);
    comp->name = buffer;
}

static component_t* component_new(const char* name, size_t size)
{
    component_t* comp = (component_t*)malloc(size);
    CHECK_RET(comp, NULL, "cannot allocate space for component");
    memset(comp, 0, size);
    comp->set_name = _set_name;

    SDL_Log("component [%s] has [%d] bytes for memory space", name, size);

    comp->set_name(comp, name);
    comp->next = NULL;
    comp->prev = NULL;
    comp->active = 1;
    comp->started = 0;

    return comp;
}

#endif