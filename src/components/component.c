#include <component.h>

#include <string.h>
#include <stdlib.h>

component_t* component_new(const char* name)
{
    component_t* comp = malloc(sizeof(component_t));
    CHECK_RET(comp, NULL, "cannot allocate space for component");
    memset(comp, 0, sizeof(component_t));

    int len = strlen(name);
    char* buffer = malloc(len + 1);
    strcpy_s(buffer, len + 1, name);
    comp->name = buffer;

    comp->next = NULL;
    comp->prev = NULL;
    comp->active = 1;
    comp->started = 0;

    return comp;
}