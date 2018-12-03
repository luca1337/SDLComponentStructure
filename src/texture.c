#include <texture.h>
#include <string.h>
#include <utils.h>
#include <stdlib.h>

extern ctx_t* ctx;

static void _draw_tex(texture_t* self)
{
    self->rect.x = self->pos.x;
    self->rect.y = self->pos.y;
    self->rect.w = self->width;
    self->rect.h = self->height;

    SDL_RenderCopyEx(ctx->renderer, self->texture, NULL, &self->rect, self->degrees, &self->pivot, self->flip_flag);
}

texture_t* texture_new(const char* path)
{
    texture_t* texture = malloc(sizeof(texture_t));
    CHECK_RET(texture, NULL, "could not allocate space for texture.")
    memset(texture, 0, sizeof(texture_t));

    int len = strlen(path);
    char* buffer = malloc(len + 1);
    strcpy_s(buffer, len + 1, path );
    texture->flip_flag = SDL_FLIP_NONE;
    texture->name = buffer;
    texture->draw_tex = _draw_tex;

    return texture;
}