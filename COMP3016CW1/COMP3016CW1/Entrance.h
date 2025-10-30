#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>

class Entrance
{
public:
	SDL_Texture* texture;
	SDL_FRect srect, drect;
	bool isSelected = false;


public:
	Entrance()
	{
		static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/DungeonEntrance.png");
		texture = tex;

		srect.h = 720;
		srect.w = 1280;
		srect.x = 0;

		drect.h = 720;
		drect.w = 1280;
	}

	virtual ~Entrance()
	{

	}

	void draw()
	{
		SDL_RenderTexture(renderer, texture, &srect, &drect);
	}
};
