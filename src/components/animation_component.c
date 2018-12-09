#include <animation_component.h>
#include <stdlib.h>
#include <string.h>

animation_component_t* animation_component_new(const char* component_name, int tiles_per_row, int* key_frames, float frame_length)
{
    animation_component_t* animation_component = malloc(sizeof(animation_component_t));
    if(!animation_component){
        fprintf(stderr, "could not allocate space for animation component\n");
        return NULL;
    }
    memset(animation_component, 0, sizeof(animation_component_t));

    animation_component->width = animation_component->sheet.width;
    animation_component->height = animation_component->sheet.height;
    animation_component->tiles_per_row = tiles_per_row;
    animation_component->key_frames = key_frames;
    animation_component->frame_length = frame_length;

    return animation_component;
}

void animation_component_init(animation_component_t* comp)
{

}