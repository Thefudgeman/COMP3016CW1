#pragma once
#include <SDL3/SDL.h>
#include <SDL3/sdl_image.h>

SDL_Window* window = SDL_CreateWindow("Title", 1280, 720, NULL);

SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
