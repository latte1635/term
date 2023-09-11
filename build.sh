#!/bin/bash
gcc -std=c2x -Wall -Wextra -pedantic main.c app.c character.c thing.c video.c -lSDL2 -o app
