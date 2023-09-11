#include "app.h"
#include "character.h"
#include "video.h"
#include "defs.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

SDL_Surface* LoadMedia(char* filename) {
    SDL_Surface* media = SDL_LoadBMP(filename);
    if(media == NULL) {
        printf("unable to load file \"%s\"\nSDL Error: %s\n", filename, SDL_GetError());
        exit(1);
    }
    return media;
}

static int App_ResizeWindowEvent(void* data, SDL_Event* event) {
    if(event->type == SDL_WINDOWEVENT &&
            event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        SDL_Window* win = SDL_GetWindowFromID(event->window.windowID);
        App* app = (App*)data;
        if (win == (SDL_Window*)app->window) {
            SDL_GetWindowSize(win, &app->windowW, &app->windowH);
            app->surface = SDL_GetWindowSurface(app->window);
            SDL_UpdateWindowSurface(app->window);
        }
    }
    if(event->type == SDL_WINDOWEVENT 
            && event->window.event == SDL_WINDOWEVENT_RESTORED) {
        SDL_Window* win = SDL_GetWindowFromID(event->window.windowID);
        App* app = (App*)data;
        if (win == (SDL_Window*)app->window) {
            SDL_GetWindowSize(win, &app->windowW, &app->windowH);
            SDL_UpdateWindowSurface(app->window);
        }
    }
    return 0;
}

void App_Init(App* app, char* windowName, int windowWidth, int windowHeight) {
    *app = (App){0};
    app->windowName = windowName;
    app->windowW = windowWidth;
    app->windowH = windowHeight;
    Video_Init(app);
    SDL_AddEventWatch(App_ResizeWindowEvent, app);
}

void App_AddCharacter(App* app, const wchar_t c, int posX, int posY, int textScale, SDL_Color color) {
    int idx = 0;
    while(app->charSlots[idx] == 1 && idx < 20000) {
        idx++;
    }
    Character character = C_GetCharFromSheet(c, color); 
    character.dstRect = (SDL_Rect) {.x = posX, .y = posY, .w = 10 * textScale, .h = 10 * textScale};
    app->characters[idx] = character; 
    app->charSlots[idx] = 1;
    app->charCount++;
}

wchar_t GetUmlauts(wchar_t wc) {
    if(wc == L'ä') {
        return 132;
    }
    else if(wc == L'å') {
        return 134;
    }else if(wc == L'ö') {
        return 148;
    }
    return wc;
} 

void App_AddString(App* app, const wchar_t* string, 
        int posX, int posY, int textScale, SDL_Color color) {
    for(int i = 0; i < wcslen(string); i++) {
        wchar_t c = GetUmlauts(string[i]);
        wprintf(L"ascii: %C=%d\n", string[i], string[i]);
        App_AddCharacter(app, c, posX + i * 10 * textScale, posY, textScale, color); 
    }
}

void App_AddThing(App* app, Thing* thing) {
    if(thing == NULL) {
        printf("App_AddThing: thing was null...\n");
        exit(0);
    }
    if(thing->texture == NULL) {
        printf("App_AddThing: thing had no texture...\n");
        exit(0);
    }
    if(thing->name == NULL) {
        printf("App_AddThing: name of thing was NULL...\n");
        exit(0);
    }
    int idx = 0;
    while(app->thingSlots[idx] == 1 && idx < 20000) {
        idx++;
    }
    app->things[idx] = *thing;
    app->thingSlots[idx] = 1;
    app->thingCount++;
}

void App_Update(App* app) {
    SDL_Delay(20);
    SDL_Event e; 
    //SDL_SetRenderDrawColor(app->renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);

    while(app->quit == FALSE) {
        SDL_RenderClear(app->renderer);
        SDL_FillRect(app->surface, NULL, 
                SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), 
                40, 
                40, 
                40, 
                SDL_ALPHA_OPAQUE));
        app->things[0].rect.w = app->windowW;
        app->things[0].rect.h = app->windowH;
        for(int i = 0; i < app->thingCount; i++) {
            if(app->thingSlots[i] == 1) {
                Thing thing = app->things[i];
                SDL_BlitScaled(thing.texture, NULL, app->surface, &thing.rect);
            }
        }
        Character character = (Character) {
            .characterTex = LoadMedia("media/chars.bmp"),
            .srcRect = (SDL_Rect) {.x =40, .y=80, .w=10, .h=10},
            .dstRect = (SDL_Rect) {.x=500, .y=500, .w=20, .h=20}
        };
        SDL_BlitScaled(character.characterTex, &character.srcRect, app->surface, &character.dstRect);
        for(int i = 0; i < app->charCount; i++) {
            if(app->charSlots[i] == 1) {
                Character character = app->characters[i];
                SDL_BlitScaled(character.characterTex, &character.srcRect, 
                        app->surface, &character.dstRect);
            } 
        } 

        SDL_UpdateWindowSurface(app->window);
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT) {
            app->quit = TRUE;
        } 
    }
    Video_Cleanup(app);
}




