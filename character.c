#include "character.h"
#include "app.h"

Character C_GetCharFromSheet(wchar_t c, SDL_Color textColor) {
    SDL_Surface* characterTex = LoadMedia("media/chars.bmp");
    int charWidth = 10, charHeight = 10;
    int x = (c % 16) * charWidth; 
    int y = (c / 16) * charHeight;
    wprintf(L"getting char from x:%d, y:%d\n", x, y); 
    SDL_Rect srcRect = {
        .x=x,
        .y=y,
        .w=charWidth, 
        .h=charHeight
    };
    return (Character){.characterTex=characterTex, .srcRect=srcRect};
}
