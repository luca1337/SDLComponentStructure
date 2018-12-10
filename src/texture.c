#include <texture.h>
#include <string.h>
#include <utils.h>
#include <stdlib.h>

extern ctx_t* ctx;

static void _draw_tex(texture_t* self)
{
    self->rect.x = self->position.x;
    self->rect.y = self->position.y;
    self->rect.w = self->width * self->scale.x;
    self->rect.h = self->height * self->scale.y;

    SDL_RenderCopyEx(ctx->renderer, self->texture, NULL, &self->rect, self->rotation, &self->pivot, self->flip_flag);
}

static void _draw_tex_tiled(texture_t* self, int x_index, int y_index, int width, int height)
{
    self->rect.x = self->position.x;
    self->rect.y = self->position.y;
    self->rect.w = width * self->scale.x;
    self->rect.h = height * self->scale.y;

    self->src.x = x_index;
    self->src.y = y_index;
    self->src.w = width;
    self->src.h = height;

    SDL_RenderCopyEx(ctx->renderer, self->texture, &self->src, &self->rect, self->rotation, &self->pivot, self->flip_flag);
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
    texture->draw_tex_tiled = _draw_tex_tiled;

    return texture;
}