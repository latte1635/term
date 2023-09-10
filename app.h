#ifndef __APP_H__
#define __APP_H__

#include "structs.h"

void App_Init(App* app, char* windowName, int windowWidth, int windowHeight);
void App_Update(App* app);
void App_AddThing(App* app, Thing* thing);
SDL_Surface* App_LoadMedia(App* app, char* filename);

#endif
