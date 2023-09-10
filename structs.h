#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <SDL2/SDL.h>

typedef struct app {
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* surface;
    int windowW;
    int windowH;
} App;

#endif
