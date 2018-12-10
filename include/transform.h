#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <component.h>
#include <vec.h>

typedef struct transform{
    component_t component;
    vec2_t position;
    float rotation;
    vec2_t scale;
}transform_t;

void transform_component_init();

#endif