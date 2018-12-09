#ifndef GFX_H
#define GFX_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

typedef struct ctx{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width,height;
    int is_running;
    float screen_ratio;
    float h_width,h_height;
    double delta_seconds;
    uint64_t end;
    uint64_t start;
    const uint8_t* key_state;
    void(*post_hook_draw)(struct ctx*);
}ctx_t;

ctx_t* ctx_new(const char*, int, int, unsigned, void(*_post_hook_draw)(ctx_t*));
void ctx_update(ctx_t*);
uint8_t get_key(ctx_t*, SDL_Scancode);
void ctx_destroy(ctx_t*);

#endif