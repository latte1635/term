#include "app.h"
#include "video.h"
#include "defs.h"
#include <SDL2/SDL_video.h>


SDL_Surface* App_LoadMedia(App* app, char* filename) {
    SDL_Surface* media = SDL_LoadBMP(filename);
    if(media == NULL) {
        printf("unable to load file \"%s\"\nSDL Error: %s\n", filename, SDL_GetError());
        exit(1);
    }
    return media;
}

static int App_ResizeWindowEvent(void* data, SDL_Event* event) {
    if (event->type == SDL_WINDOWEVENT &&
            event->window.event == SDL_WINDOWEVENT_RESIZED) {
        SDL_Window* win = SDL_GetWindowFromID(event->window.windowID);
        App* app = (App*)data;
        if (win == (SDL_Window*)app->window) {
            printf("resizing.....\n");
            SDL_GetWindowSize(win, &app->windowW, &app->windowH);
        }
    }
    return 0;
}

void App_Init(App* app, char* windowName, int windowWidth, int windowHeight) {
    app->windowName = windowName;
    app->window = NULL;
    app->renderer = NULL;
    app->surface = NULL;
    app->windowW = windowWidth;
    app->windowH = windowHeight;
    app->quit = FALSE;
    app->thingCount = 0;
    Video_Init(app);
    SDL_AddEventWatch(App_ResizeWindowEvent, app);
}

void App_AddThing(App* app, Thing* thing) {
    if(thing == NULL) {
        printf("App_AddThing: thing was null...\n");
    }
    if(thing->texture == NULL) {
        printf("App_AddThing: thing had no texture...\n");
    }
    if(thing->name == NULL) {
        printf("App_AddThing: name of thing was NULL...\n");
    }
    app->things[app->thingCount] = *thing;
    app->thingCount++;
}

void App_Update(App* app) {
    SDL_Event e; 
    while(app->quit == FALSE) {
        app->things[0].rect.w = app->windowW;
        app->things[0].rect.h = app->windowH;

        for(int i = 0; i < app->thingCount; i++) {
            Thing thing = app->things[i];
            printf("%s: x:%d, y:%d\n", thing.name, thing.rect.w, thing.rect.h);
            SDL_BlitScaled(thing.texture, NULL, app->surface, &thing.rect); 
        }

        SDL_UpdateWindowSurface(app->window);
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT) {
            app->quit = TRUE;
        } 
    }
    Video_Cleanup(app);
}




