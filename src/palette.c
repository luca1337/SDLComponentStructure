#include <palette.h>
#include <stdlib.h>
#include <string.h>
#include <engine_utils.h>

palette_t* palette_new(vec2_t draw_pos, vec2_t size, player_t* ball, const char* actor_name, char side_paddle, char auto_move)
{
    palette_t* palette = malloc(sizeof(palette_t));
    CHECK_RET(palette, NULL, "could not allocate space for palette")
    memset(palette, 0, sizeof(palette_t));
    palette->actor.transform.position = draw_pos;
    palette->actor.transform.rotation = 0;
    palette->actor.transform.scale = vec2_init(1, 1);

    // add some component..
    /*palette->render_component = COMPONENT_NEW(render_component, render_component_t);
    render_component_init(palette->render_component, &palette->actor, actor_name, 1, size.x, size.y, 1);
    add_component(&palette->actor, CastToComponent(palette->render_component));

    // move component for palettes
    palette->move_component = COMPONENT_NEW(move_component, move_component_t);
    move_component_init(palette->move_component, CastToActor(palette), ball, side_paddle, auto_move);
    add_component(&palette->actor, CastToComponent(palette->move_component));*/

    palette->width = palette->render_component->sprite->width;
    palette->height = palette->render_component->sprite->height;

    return palette;
}