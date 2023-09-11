#include <wchar.h>
#include "structs.h"
#include "thing.h"
#include "app.h"
#include <SDL2/SDL_events.h>
#include <locale.h>



int main(int argc, char* args[]) {
    setlocale(LC_ALL, "");
    App app;
    App_Init(&app, "siili", 800, 600);
    Thing siili;
    SDL_Rect siiliRect = {.w=400, .h=400};
    SDL_Surface* siiliTex = LoadMedia("media/siilimakaa.bmp");
    Thing_Init(&siili, "siili", siiliRect, siiliTex);
    wprintf(L"muh ääkköset...\n");
    wprintf(L"test: %c\n", L'ä');
    SDL_Color textColor = (SDL_Color) {255, 255, 255, 255};
    //App_AddCharacter(&app, 'H', 50, 50, textColor); 
    App_AddString(&app, L"abcdefghijklmnopqrstuvwxyzåäö", 180, 200, 2, textColor);
    App_AddThing(&app, &siili);
    App_Update(&app);
    return 0;
}
