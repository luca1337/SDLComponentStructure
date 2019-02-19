#ifndef PHYSICS_H
#define PHYSICS_H

#include <collider.h>
#include <rigid_body.h>
#include <hit_state.h>

// #define check_sign(x) (x == 0) ? 0 : (x < 0) ? -1 : (x > 0) ? 1 : 0

int intersect(collider_t* a, collider_t* b)
{
    if(a->owner->transform.position.x + a->width > b->owner->transform.position.x
    && a->owner->transform.position.x < b->owner->transform.position.x + b->width
    && a->owner->transform.position.y + a->height > b->owner->transform.position.y
    && a->owner->transform.position.y < b->owner->transform.position.y + b->height)
    {
        return 1;
    }
    return 0;
}

int check_sign(int num)
{
    if(num == 0)
        return 0;
    else if(num < 0)
        return -1;
    else if(num > 0)
        return 1;

    return 2;
}

hit_state_t aabb(collider_t* a, collider_t* b)
{
    hit_state_t hit_state;
    memset(&hit_state, 0, sizeof(hit_state_t));

    float dx = b->get_center(b).x - a->get_center(a).x;
    float px = (b->get_half_size(b).x + a->get_half_size(a).x) - _abs64(dx);

    if(px <= 0.0f)
    {
        return hit_state;
    }

    float dy = b->get_center(b).y - a->get_center(a).y;
    float py = (b->get_half_size(b).y + a->get_half_size(a).y) - _abs64(dy);

    if (py <= 0.0f)
    {
        return hit_state;
    }

    hit_state.hit = 1;

    if (px < py)
    {
        //normal is on x axis
        int sx = check_sign(dx);
        hit_state.normal = vec2_init(-sx, 0);
    }
    else
    {
        //normal is on y axis
        int sy = check_sign(dy);
        hit_state.normal = vec2_init(0, -sy);
    }

    return hit_state;
}

void change_position(collider_t* a, collider_t* b, vec2_t normal)
{
    //Stop rigidbody
    vec2_t position = a->owner->transform.position;
    vec2_t position2 = b->owner->transform.position;
    rigid_body_t* rb = (rigid_body_t*)get_component_by_name(a->owner, "rigid_body");

    // if(!rb) { SDL_Log("rigid_body not while resolving collisions"); return; }

    //hit from dx
    if (normal.x > 0.0f && position.x < b->owner->transform.position.x + b->size.x)
    {
        rb->velocity.x = 0.0f;
        // SDL_Log("collided dx");
        position.x = (b->owner->transform.position.x + b->size.x) + 0.7f;
    }

    //hit from sx
    if (normal.x < 0.0f && position.x + a->size.x > b->owner->transform.position.x)
    {
        rb->velocity.x = 0.0f;

        float offset = b->size.x - a->size.x;
        float offset2 = a->size.x - b->size.x;
        // SDL_Log("collided sx");
        position.x = (b->owner->transform.position.x - b->size.x) + offset;
        position2.x = (a->owner->transform.position.x - a->size.x) + offset2;
    }

    //hit from top
    if (normal.y < 0.0f && position.y + a->size.y > b->owner->transform.position.y)
    {
        rb->velocity.y = 0.0f;
        float offset = b->size.y - a->size.y;
        position.y = (b->owner->transform.position.y - b->size.y) + offset;
    }

    //hit from bottom
    if (normal.y > 0.0f && position.y < b->owner->transform.position.y + b->size.y)
    {
        rb->velocity.y = 0.0f;
        // SDL_Log("collided bottom");
        position.y = (b->owner->transform.position.y + b->size.y) + 0.7f;
    }

    //change pos
    a->owner->transform.position = position;
}

void resolve_collisions(collider_t* a, collider_t* b, vec2_t normal)
{
    change_position(a, b, normal);
}


#endif