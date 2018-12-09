#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <actor.h>
#include <texture.h>

typedef struct animation_component{
    component_t component;
    texture_t sheet;
    int width, height;
    int* key_frames;
    float frame_length;
    int tiles_per_row;
    float time;
    int current_index;
    int index;
}animation_component_t;

animation_component_t* animation_component_new(const char*, int, int*, float);
void animation_component_init(animation_component_t*);

#endif