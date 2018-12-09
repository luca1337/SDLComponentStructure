#include <component.h>

#include <string.h>
#include <stdlib.h>
#include <SDL.h>

static void _set_name(component_t* comp, const char* name)
{
    int len = strlen(name);
    char* buffer = malloc(len + 1);
    strcpy_s(buffer, len + 1, name);
    comp->name = buffer;
}

component_t* component_new(const char* name, int size)
{
    component_t* comp = malloc(size);
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