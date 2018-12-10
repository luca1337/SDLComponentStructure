#include <move_component.h>
#include <palette.h>
#include <gfx.h>
#include <stdlib.h>
#include <engine_utils.h>

extern ctx_t* ctx;

#define SPEED 500

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

static void _tick(move_component_t* comp)
{
    palette_t* paddle = (palette_t*)comp->paddle;

    if(!paddle) return;

    // change direction if the ball has collided with the paddle
    if(comp->ball->actor.transform.position.x < paddle->actor.transform.position.x + paddle->width
        && comp->ball->actor.transform.position.x + comp->ball->actor.transform.scale.x > paddle->actor.transform.position.x
        && comp->ball->actor.transform.position.y < paddle->actor.transform.position.y + paddle->height
        && comp->ball->actor.transform.scale.y + comp->ball->actor.transform.position.y > paddle->actor.transform.position.y)
    {
        if(comp->side_paddle==0)
        {
            //left paddle
            vec2_t reflected = vec2_reflected(comp->moveball_ref->current_direction, vec2_init(1.0f, 0.0f));
            comp->moveball_ref->current_direction = reflected;
            comp->ball->renderer->texture->flip_flag = SDL_FLIP_HORIZONTAL;
        }
        else
        {
            //right paddle
            vec2_t reflected = vec2_reflected(comp->moveball_ref->current_direction, vec2_init(-1.0f, 0.0f));
            comp->moveball_ref->current_direction = reflected;
            comp->ball->renderer->texture->flip_flag = SDL_FLIP_HORIZONTAL;
        }
    }

    if(comp->auto_move)
    {
        float max = (ctx->height - paddle->height);
        paddle->actor.transform.position.y = CLAMP(comp->ball->actor.transform.position.y, 0, max);
    }
    else
    {
        if(get_key(ctx, SDL_SCANCODE_W) && paddle->actor.transform.position.y > 0 )
        {
            paddle->actor.transform.position.y += -SPEED * ctx->delta_seconds;
        }

        if(get_key(ctx, SDL_SCANCODE_S) && paddle->actor.transform.position.y + paddle->height < ctx->height)
        {
            paddle->actor.transform.position.y += SPEED * ctx->delta_seconds;
        }
    }
}

static void _begin(move_component_t* comp)
{
    comp->paddle = (palette_t*)comp->owner;
    if(!comp->paddle){
        fprintf(stderr, "could not locate paddle owner.\n");
        exit(-1);
    }

    get_component(CastToActor(comp->ball), "moveball_component", (component_t**)&comp->moveball_ref);
    if(!comp->moveball_ref){
        fprintf(stderr, "could not retrieve the component 'bounce'\n");
    }

    comp->component.started = 1;
}

void move_component_init(move_component_t* comp, actor_t* owner, player_t* ball, char side_paddle, char auto_move)
{
    comp->owner = owner;
    comp->ball = ball;
    comp->side_paddle = side_paddle;
    comp->auto_move = auto_move;
    comp->component.tick = (void(*)(component_t*))_tick;
    comp->component.begin = (void(*)(component_t*))_begin;
}