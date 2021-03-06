#include <animation_component.h>
#include <stdlib.h>
#include <string.h>
#include <engine_utils.h>
#include <texture_mgr.h>
#include <math.h>

#define speed 150

extern ctx_t* ctx;
extern texture_mgr_t* mgr;

static void _tick(animation_component_t* comp)
{
    comp->sprite->position = comp->owner->transform.position;
    comp->sprite->rotation = comp->owner->transform.rotation;
    comp->sprite->scale = comp->owner->transform.scale;

    // try to move it
    /*if(get_key(ctx, SDL_SCANCODE_D))
        comp->owner->transform.position.x += speed * ctx->delta_seconds;

    if(get_key(ctx, SDL_SCANCODE_A))
        comp->owner->transform.position.x += -speed * ctx->delta_seconds;

    if(get_key(ctx, SDL_SCANCODE_W))
        comp->owner->transform.position.y += -speed * ctx->delta_seconds;

    if(get_key(ctx, SDL_SCANCODE_S))
        comp->owner->transform.position.y += speed * ctx->delta_seconds;*/

    //rot around center of mass
    // comp->owner->transform.rotation += speed * ctx->delta_seconds;

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

    comp->sprite->draw_texture_tiled(comp->sprite, x_index, y_index, comp->width, comp->height);
}

static void _begin(animation_component_t* comp)
{
    comp->timer = 0;

    comp->component.started = 1;
}

void animation_component_init(animation_component_t* comp, actor_t* owner, const char* texture_name, int tiles_per_row, int tiles_per_column, int* key_frames, int number_of_keys, float frame_length)
{
    comp->owner = owner;
    texture_t* texture = get_texture(mgr, texture_name);
    comp->sprite = sprite_new(texture->width, texture->height);
    comp->sprite->texture = texture->texture;
    comp->tiles_per_row = tiles_per_row;
    comp->tiles_per_column = tiles_per_column;
    comp->key_frames = key_frames;
    comp->frame_length = frame_length;
    comp->num_of_key_frames = number_of_keys - 1;
    comp->width = comp->sprite->width / comp->tiles_per_row;
    comp->height = comp->sprite->height / comp->tiles_per_column;

    // pivot ?
    comp->sprite->pivot.x = (comp->width * comp->owner->transform.scale.x) / 2;
    comp->sprite->pivot.y = (comp->height * comp->owner->transform.scale.y) / 2;

    comp->component.tick = CastToFuncPtr(_tick, component_t);
    comp->component.begin = CastToFuncPtr(_begin, component_t);
}