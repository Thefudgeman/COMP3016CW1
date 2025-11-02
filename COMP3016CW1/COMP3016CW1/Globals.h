#pragma once
#include <SDL3/SDL.h>
#include <SDL3/sdl_image.h>

SDL_Window* window = SDL_CreateWindow("Title", 1280, 720, NULL);

SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

int currentFloor = 1;
int actionsOnFloorTaken = 0;
int highestFloor = 1;
bool gameVictory = false;
