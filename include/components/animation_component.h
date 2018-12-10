#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <actor.h>
#include <texture.h>

typedef struct animation_component{
    component_t component;
    texture_t* sheet;
    int width, height;
    int* key_frames;
    float frame_length;
    int tiles_per_row;
    int tiles_per_column;
    float timer;
    int current_index;
    int num_of_key_frames;
    int index;
}animation_component_t;

void animation_component_init(animation_component_t* comp, const char* texture_name, int tiles_per_row, int tiles_per_column, int* key_frames, int number_of_keys, float frame_length);

#endif