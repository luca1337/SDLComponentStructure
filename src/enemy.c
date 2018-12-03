#include <enemy.h>
#include <stdlib.h>
#include <utils.h>

#include <texture_mgr.h>
#include <engine.h>

#include <engine_utils.h>

enemy_t* enemy_new(vec2_t pos, const char* name)
{
    // crate player 
    enemy_t* player = malloc(sizeof(enemy_t));
    CHECK_RET(player, NULL, "could not allocate space for player struct\n");
    memset(player, 0, sizeof(enemy_t));
}