#ifndef __INIT_H__
#define __INIT_H__

#include "structs.h"

void App_Init(App* app, int windowWidth, int windowHeight);
void App_Update(App* app);
void Video_Init(App* app);
void Video_Cleanup(App* app);


#endif
