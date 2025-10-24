#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "Globals.h"

class Mouse
{
	SDL_Texture* texture;
	SDL_FRect rect;
	

	public:
		SDL_FRect point;
		Mouse()
		{
			texture = IMG_LoadTexture(renderer, "images/mouse.png");
			rect.w = 25;
			rect.h = 25;
			point.w = 1;
			point.h = 1;

			SDL_HideCursor();
		}
		void update()
		{
			SDL_GetMouseState(&rect.x, &rect.y);
			point.x = rect.x;
			point.y = rect.y;
		}

		void draw()
		{
			SDL_RenderTexture(renderer, texture, NULL, &rect);
		}
};