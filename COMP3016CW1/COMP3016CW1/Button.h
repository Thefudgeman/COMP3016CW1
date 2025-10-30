#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>
#include "UIObject.h"

class Button : public UIObject
{

public:
	Button()
	{
		static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/Buttons2.png");
		texture = tex;

		srect.h = 210;
		srect.w = 625;
		srect.x = 0;

		drect.h = 105;
		drect.w = 300;
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
