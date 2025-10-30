#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>
#include "UIObject.h"

class ActionsBox : public UIObject
{

public:
	ActionsBox()
	{
		static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/ActionsBox.png");
		texture = tex;

		srect.h = 220;
		srect.w = 1260;
		srect.x = 0;

		drect.h = 220;
		drect.w = 1260;
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
