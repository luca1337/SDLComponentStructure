#include <animation_component.h>
#include <stdlib.h>
#include <string.h>
#include <engine_utils.h>
#include <texture_mgr.h>

extern ctx_t* ctx;
extern texture_mgr_t* mgr;

static void _tick(animation_component_t* comp)
{
    comp->time += ctx->delta_seconds;
    if(comp->time > comp->frame_length)
    {
        if(comp->index > 2)
        {
            comp->current_index = comp->key_frames[0];
            comp->index = 0;
            SDL_Log("Reset!");
        }

        comp->current_index = comp->key_frames[comp->index++];
        SDL_Log("Current X [%d] | Current Y [%d]", (comp->current_index  % comp->tiles_per_row) * 64, (comp->current_index  / comp->tiles_per_row) * 64);
        comp->time = 0.0f;
    }

    int x_index = (comp->current_index  % comp->tiles_per_row) * 64;
    int y_index = (comp->current_index  / comp->tiles_per_row) * 64;

    comp->sheet->draw_tex_tiled(comp->sheet, x_index, y_index, 64, 64);
}

static void _begin(animation_component_t* comp)
{
    comp->component.started = 1;
}

void animation_component_init(animation_component_t* comp, const char* texture_name, int tiles_per_row, int* key_frames, float frame_length)
{
    comp->sheet = get_texture(mgr, texture_name);
    comp->width = comp->sheet->width;
    comp->height = comp->sheet->height;
    comp->tiles_per_row = tiles_per_row;
    comp->key_frames = key_frames;
    comp->frame_length = frame_length;

    comp->component.tick = CastToFuncPtr(_tick, component_t);
    comp->component.begin = CastToFuncPtr(_begin, component_t);
}