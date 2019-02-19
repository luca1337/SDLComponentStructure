#include <enemy.h>
#include <stdlib.h>
#include <utils.h>

#include <texture_mgr.h>
#include <engine.h>

#include <engine_utils.h>

enemy_t* enemy_new(vec2_t pos, const char* texture_name)
{
    // crate enemy 
    enemy_t* enemy = malloc(sizeof(enemy_t));
    CHECK_RET(enemy, NULL, "could not allocate space for enemy struct\n");
    memset(enemy, 0, sizeof(enemy_t));
    enemy->actor.transform.position = pos;
    enemy->actor.transform.rotation = 0;
    enemy->actor.transform.scale = vec2_init(1, 1);

    //animation component
    int num_of_keys = 27;
    int* key_frames = (int*)malloc(sizeof(int) * num_of_keys);
    int i = 0;
    for(; i < num_of_keys; i++){
        key_frames[i] = i;
    }
    enemy->animation_renderer = COMPONENT_NEW(animation_component, animation_component_t);
    animation_component_init(enemy->animation_renderer, &enemy->actor, texture_name, 7, 4, key_frames, num_of_keys, 0.02f);
    add_component(&enemy->actor, CastToComponent(enemy->animation_renderer));

    //collider component
    enemy->collider = COMPONENT_NEW(collider, collider_t);
    collider_init(enemy->collider, &enemy->actor, (enemy->animation_renderer->width), enemy->animation_renderer->height);
    add_component(&enemy->actor, CastToComponent(enemy->collider));
    enemy->collider->debug = 1;

    SDL_Log("enemy center_x: [%.2f] enemy center_y [%.2f]", enemy->collider->get_half_size(enemy->collider).x, enemy->collider->get_half_size(enemy->collider).y);

    //rigid bodyyy
    enemy->rb = COMPONENT_NEW(rigid_body, rigid_body_t);
    rigid_body_init(enemy->rb, &enemy->actor, 0);
    add_component(&enemy->actor, CastToComponent(enemy->rb));

    return enemy;
}