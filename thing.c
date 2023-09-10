#include "thing.h"
#include <string.h>

void Thing_Init(Thing* thing, const char* name, SDL_Rect rect, SDL_Surface* texture) {
    thing->name = malloc(strlen(name) + 1);
    strcpy(thing->name, name);
    thing->rect = rect;
    thing->texture = texture;
}
