#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>
#include "UIObject.h"

class GameButtons : public UIObject
{

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
};
