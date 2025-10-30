#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>

class DungeonRoom
{
public:
	SDL_Texture* texture;
	SDL_FRect srect, drect;
	bool isSelected = false;


public:
	DungeonRoom()
	{
		static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/DungeonRoom.png");
		texture = tex;

		srect.h = 720;
		srect.w = 1280;
		srect.x = 0;

		drect.h = 720;
		drect.w = 1280;
	}

	virtual ~DungeonRoom()
	{

	}

	void draw()
	{
		SDL_RenderTexture(renderer, texture, &srect, &drect);
	}
};
#pragma once
