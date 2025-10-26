#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>

class MinusStatButton
{
public:
	SDL_Texture* texture;
	SDL_FRect srect, drect;
	bool isSelected = false;


public:
	MinusStatButton()
	{
		static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/Minus.png");
		texture = tex;

		srect.h = 32;
		srect.w = 32;
		srect.x = 0;

		drect.h = 32;
		drect.w = 32;
	}

	virtual ~MinusStatButton()
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
