#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

typedef struct texture{
    SDL_Texture* texture;
    char* name;
    int width, height;
    uint8_t* bitmap;
}texture_t;

texture_t* texture_new(const char* file_path);

#endif