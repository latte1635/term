#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct THING {
    char* name;
    SDL_Surface* texture;
    SDL_Rect rect;
} Thing;

typedef struct CHARACTER {
    SDL_Surface* characterTex;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
} Character;

typedef struct APP {
    char* windowName;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* surface;
    int windowW;
    int windowH;
    int quit;
    Thing things[128];
    int thingSlots[128];
    int thingCount;
    Character characters[20000];
    int charSlots[20000];
    int charCount;
} App;

#endif
