#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>
#include "UIObject.h"

class PlusStatButton : public UIObject
{

public:
	PlusStatButton()
	{
		static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/Plus.png");
		texture = tex;

		srect.h = 32;
		srect.w = 32;
		srect.x = 0;

		drect.h = 32;
		drect.w = 32;
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
