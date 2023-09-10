#include "structs.h"
#include "thing.h"
#include "app.h"
#include <SDL2/SDL_events.h>


int main(int argc, char* args[]) {
    App app;
    App_Init(&app, "siili", 800, 600);
    Thing siili;
    SDL_Rect siiliRect = {.w = app.windowW, .h = app.windowH};
    SDL_Surface* siiliTex = App_LoadMedia(&app, "media/siilimakaa.bmp");
    Thing_Init(&siili, "siili", siiliRect, siiliTex);
    App_AddThing(&app, &siili);
    App_Update(&app);
    return 0;
}
