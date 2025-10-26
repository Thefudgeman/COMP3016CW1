#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>

class GameButtons
{
public:
	SDL_Texture* texture;
	SDL_FRect srect, drect;
	bool isSelected = false;


public:
	GameButtons()
	{
		static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/GameButtons2.png");
		texture = tex;

		srect.h = 105;
		srect.w = 312;
		srect.x = 0;

		drect.h = 105;
		drect.w = 312;
	}

	virtual ~GameButtons()
	{

	}

	void update(Mouse& mouse)
	{
		if (SDL_HasRectIntersectionFloat(&drect, &mouse.point))
		{
			isSelected = true;
			srect.x = 0;
		}
		else
		{
			isSelected = false;
			srect.x = 0;
		}
	}

	void draw()
	{
		SDL_RenderTexture(renderer, texture, &srect, &drect);
	}
};
