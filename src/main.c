#define SDL_MAIN_HANDLED

#include <logic.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main(int argc, char** argv)
{
    game_manager_t* gm = game_manager_new();
    gm->init(gm);
    gm->tick(gm);

    return 0;
}