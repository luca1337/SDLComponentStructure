#ifndef COLLIDER_H
#define COLLIDER_H


typedef struct collider{
    void(*debug_draw_collider)(struct collider* collider);
}collider_t;

#endif