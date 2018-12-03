#include <palette.h>
#include <stdlib.h>
#include <string.h>
#include <engine_utils.h>

palette_t* palette_new(vec2_t draw_pos, vec2_t size, player_t* ball, const char* actor_name, char side_paddle, char auto_move)
{
    palette_t* palette = malloc(sizeof(palette_t));
    CHECK_RET(palette, NULL, "could not allocate space for palette")
    memset(palette, 0, sizeof(palette_t));

    // add some component..
    palette->render_component = render_component_new("palette_visualizer");
    render_component_init(palette->render_component, actor_name, 1, size.x, size.y, 1);
    add_component(&palette->actor, CastToComponent(palette->render_component));

    // move component for palettes
    palette->move_component = move_component_new("palette_mover");
    move_component_init(palette->move_component, CastToActor(palette), ball, side_paddle, auto_move);
    add_component(&palette->actor, CastToComponent(palette->move_component));

    palette->render_component->sprite->pos.x = draw_pos.x;
    palette->render_component->sprite->pos.y = draw_pos.y;

    palette->pos.x = draw_pos.x;
    palette->pos.y = draw_pos.y;

    palette->width = size.x;
    palette->height = size.y;

    return palette;
}