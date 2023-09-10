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
            "SDL Tutorial", 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            app->windowW, 
            app->windowH,
            SDL_WINDOW_SHOWN
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

void App_Update(App* app) {
     
    
}

SDL_Surface* App_LoadMedia(App* app, char* filename) {
     SDL_Surface* media = SDL_LoadBMP(filename);
     if(media == NULL) {
        printf("unable to load file \"%s\"\nSDL Error: %s\n", filename, SDL_GetError());
        exit(1);
     }
     return media;
}

void App_Init(App* app, int windowWidth, int windowHeight) {
    app->window = NULL;
    app->renderer = NULL;
    app->surface = NULL;
    app->windowW = windowWidth;
    app->windowH = windowHeight;

    Video_Init(app);
    
    SDL_Surface* siilimakaa = App_LoadMedia(app, "media/siilimakaa.bmp"); 
    SDL_Surface* siilismile = App_LoadMedia(app, "media/siilismile.bmp");
    SDL_Rect srcRect = {
        .x = 1,
        .y = 1,
        .w = siilimakaa->w / 2.0f,
        .h = siilimakaa->h / 2.0f
    };

    SDL_Rect screenRect = {
        .x = app->windowW / 2.0f,
        .y = app->windowH / 2.0f,
        .w = siilimakaa->w / 2.0f,
        .h = siilimakaa->h / 2.0f
    };
     
    int dir = 1;

    SDL_Event e; 
    int quit = FALSE; 
    while(quit == FALSE) {   
        App_Update(app);

        if(screenRect.w > siilimakaa->w || screenRect.w < siilimakaa->w / 3.0f) {
            dir *= -1;
        }

        screenRect.w += 1.0 * dir;

        SDL_BlitScaled(siilimakaa, NULL, app->surface, &screenRect); 
        SDL_BlitSurface(siilismile, NULL, app->surface, NULL); 
        SDL_UpdateWindowSurface(app->window);
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT) {
            quit = TRUE;
        } 
    }
    Video_Cleanup(app);
}
