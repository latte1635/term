#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include "structs.h"

#define TRUE 1
#define FALSE 0


void Video_Init(App* app) {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;
    
    if(SDL_Init(SDL_INIT_VIDEO)) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    app->window = SDL_CreateWindow(
            app->windowName,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            app->windowW, 
            app->windowH,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
            );
    
    if(app->window == NULL) {
        printf("Window could not be created: %s\n", SDL_GetError());
        exit(1);
    }

    app->surface = SDL_GetWindowSurface(app->window);
}

void Video_Cleanup(App* app) {
    SDL_FreeSurface(app->surface);
    app->surface = NULL;

    SDL_DestroyWindow(app->window);
    app->window = NULL;

    SDL_Quit();
}


