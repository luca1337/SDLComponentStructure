#include <animation_component.h>
#include <stdlib.h>
#include <string.h>
#include <engine_utils.h>
#include <texture_mgr.h>

#define speed 150

extern ctx_t* ctx;
extern texture_mgr_t* mgr;

static void _tick(animation_component_t* comp)
{
    comp->sheet->position = comp->owner->transform.position;
    comp->sheet->rotation = comp->owner->transform.rotation;
    comp->sheet->scale = comp->owner->transform.scale;

    // try to move it
    if(get_key(ctx, SDL_SCANCODE_U))
        comp->sheet->position.x += speed * ctx->delta_seconds;

    comp->timer += ctx->delta_seconds;
    if(comp->timer > comp->frame_length)
    {
        if(comp->index > comp->num_of_key_frames)
        {
            comp->current_index = comp->key_frames[0];
            comp->index = 0;
        }
        comp->current_index = comp->key_frames[comp->index++];
        comp->timer = 0.0f;
    }

    int x_index = (comp->current_index  % comp->tiles_per_row) * comp->width;
    int y_index = (comp->current_index  / comp->tiles_per_row) * comp->height;

    comp->sheet->draw_tex_tiled(comp->sheet, x_index, y_index, comp->width, comp->height);
}

static void _begin(animation_component_t* comp)
{
    comp->timer = 0;

    comp->component.started = 1;
}

void animation_component_init(animation_component_t* comp, actor_t* owner, const char* texture_name, int tiles_per_row, int tiles_per_column, int* key_frames, int number_of_keys, float frame_length)
{
    comp->owner = owner;
    comp->sheet = get_texture(mgr, texture_name);
    comp->tiles_per_row = tiles_per_row;
    comp->tiles_per_column = tiles_per_column;
    comp->key_frames = key_frames;
    comp->frame_length = frame_length;
    comp->num_of_key_frames = number_of_keys - 1;
    comp->width = comp->sheet->width / comp->tiles_per_row;
    comp->height = comp->sheet->height / comp->tiles_per_column;

    comp->component.tick = CastToFuncPtr(_tick, component_t);
    comp->component.begin = CastToFuncPtr(_begin, component_t);
}