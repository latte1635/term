#ifndef __APP_H__
#define __APP_H__

#include "structs.h"

void App_Init(App* app, char* windowName, int windowWidth, int windowHeight);
void App_Update(App* app);
void App_AddThing(App* app, Thing* thing);
void App_AddCharacter(App* app, wchar_t c, int posX, int posY, int textScale, SDL_Color color); 
void App_AddString(App* app, const wchar_t* string, 
        int posX, int posY, int textScale, SDL_Color color); 
SDL_Surface* LoadMedia(char* filename);

#endif
