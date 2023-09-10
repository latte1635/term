#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <SDL2/SDL.h>

typedef struct THING {
    char* name;
    SDL_Surface* texture;
    SDL_Rect rect;
} Thing;

typedef struct APP {
    char* windowName;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* surface;
    int windowW;
    int windowH;
    int quit;
    Thing things[128];
    int thingCount;
} App;

#endif
