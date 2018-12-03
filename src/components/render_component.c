#include <render_component.h>
#include <texture_mgr.h>
#include <string.h>
#include <stdlib.h>

extern ctx_t* ctx;
extern texture_mgr_t* mgr;

static void tick(render_component_t* c)
{
    // wat else ?
    if(c->texture) // i'm not gonna crash
    {
        c->texture->draw_tex(c->texture);
    }
    else
    {
        c->sprite->draw_sprite(c->sprite, 255, 0, 0, 255);
    }
}

render_component_t* render_component_new(const char* name)
{
    render_component_t* comp = malloc(sizeof(render_component_t));
    if(!comp){
        return NULL;
    }
    memset(comp, 0, sizeof(render_component_t));
    int len = strlen(name);
    char* buffer = malloc(len + 1);
    strcpy_s(buffer, len + 1, name);
    comp->component.name = buffer;
    comp->component.active = 1;
    return comp;
}

void render_component_init(render_component_t* c, const char* name, int sprite_mode, int width, int height, int pivot)
{
    // i don't like this shit
    if(sprite_mode == 0)
    {
        printf("texture mode\n");
        c->texture = get_texture(mgr, name);
    }
    else if(sprite_mode == 1)
    {
        printf("sprite mode\n");
        c->sprite = sprite_new(width, height, pivot);
    }

    printf("gonna tick\n");
    c->component.tick = (void(*)(component_t*))tick;
}