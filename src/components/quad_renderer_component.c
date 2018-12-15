#include <quad_renderer_component.h>

static void _tick(quad_renderer_t* component)
{
    component->sprite->position = component->owner->transform.position;
    component->sprite->rotation = component->owner->transform.rotation;
    component->sprite->scale = component->owner->transform.scale;

    color_t col = {255, 0, 255, 255};
    component->sprite->draw_sprite_color(component->sprite, col);
}

static void _begin(quad_renderer_t* component)
{
    component->component.started = 1;
}

void quad_renderer_init(quad_renderer_t* quad_renderer, actor_t* owner, int width, int height)
{
    quad_renderer->owner = owner;

    quad_renderer->sprite = sprite_new(width, height);

    quad_renderer->sprite->pivot.x = (quad_renderer->sprite->width * quad_renderer->owner->transform.scale.x) / 2;
    quad_renderer->sprite->pivot.y = (quad_renderer->sprite->height * quad_renderer->owner->transform.scale.y) / 2;

    // quad_renderer->sprite->change_sprite_color(quad_renderer->sprite, 0, 0, 255, 255);

    quad_renderer->component.begin = CastToFuncPtr(_begin, component_t);
    quad_renderer->component.tick = CastToFuncPtr(_tick, component_t);
}