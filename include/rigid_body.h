#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include <actor.h>
#include <vec.h>

typedef struct rigid_body{
    component_t component;
    actor_t* owner;
    vec2_t velocity;
    char is_gravity_affected;
    float linear_friction;
    void(*rigid_body_add_force)(struct rigid_body* rigid_body, vec2_t force);
}rigid_body_t;

void rigid_body_init(rigid_body_t* comp, actor_t* owner, char gravity_affected);

#endif