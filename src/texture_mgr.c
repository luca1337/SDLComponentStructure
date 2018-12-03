#include <texture_mgr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <stb_image.h>

texture_mgr_t* texture_mrg_new()
{
    texture_mgr_t* texture_mgr = malloc(sizeof(texture_mgr_t));
    CHECK_RET(texture_mgr, NULL, "could not create texture manager.")

    memset(texture_mgr, 0, sizeof(texture_mgr_t));

    texture_mgr->textures = tex_list_new(NULL);

    return texture_mgr;
}

texture_t* add_texture(ctx_t* ctx, texture_mgr_t* t_mgr, const char* name, const char* file_name, uint32_t format, int access, int channels)
{
    texture_t* tex = texture_new(file_name);

    int width, height, color_channel;
    unsigned char* data = stbi_load(file_name, &width, &height, &color_channel, channels);

    SDL_Texture* new_tex = SDL_CreateTexture(ctx->renderer, format, access, width, height);
    SDL_LOG(new_tex, NULL);

    int pitch = 0;

    unsigned char* pixel = NULL;

    if (SDL_LockTexture(new_tex, NULL, (void **)&pixel, &pitch))
    {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
        return NULL;
    }

    memset(pixel, 0, width * height * color_channel);
    memcpy(pixel, data, width * height * color_channel);
    SDL_UnlockTexture(new_tex);

    int len = strlen(name);
    char* buf = malloc(len + 1);
    strcpy_s(buf, len + 1, name);

    tex->texture = new_tex;
    tex->name = buf;
    tex->id = 0;
    tex->width = width;
    tex->height = height;
    tex->pos.x = 0;
    tex->pos.y = 0;

    tex_list_append(t_mgr->textures, tex);

    return tex;
}

texture_t* get_texture(texture_mgr_t* mgr, const char* key)
{
    texture_t* tex = tex_list_get(mgr->textures, key);
    if(!tex){
        printf("sopmething wrong\n");
        return NULL;
    }
    return tex;
}

void destroy_texture_mgr(texture_mgr_t* mgr)
{
    tex_list_destroy(mgr->textures);
}
