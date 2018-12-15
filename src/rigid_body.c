#include <rigid_body.h>
#include <engine_utils.h>
#include <gfx.h>

extern ctx_t* ctx;
static vec2_t gravity = { 0, 9.81f };

static void _rigid_body_add_force(rigid_body_t* rigid_body, vec2_t force)
{
    vec2_interpolate(&rigid_body->velocity, &force, ctx->delta_seconds);
}

static void _tick(rigid_body_t* comp)
{
    if(comp->is_gravity_affected == 1)
    {
        comp->rigid_body_add_force(comp, gravity);
    }

    comp->rigid_body_add_force(comp, vec2_scaled(vec2_sub(comp->velocity, comp->velocity), comp->linear_friction));

    vec2_interpolate(&comp->owner->transform.position, &comp->velocity, ctx->delta_seconds);
}

void rigid_body_init(rigid_body_t* comp, actor_t* owner, char gravity_affected)
{
    comp->owner = owner;
    comp->is_gravity_affected = gravity_affected;
    comp->rigid_body_add_force = _rigid_body_add_force;
    comp->component.tick = CastToFuncPtr(_tick, component_t);
}