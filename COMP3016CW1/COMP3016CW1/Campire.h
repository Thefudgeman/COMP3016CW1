#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>
#include "UIObject.h"

class Campfire : public UIObject
{

public:
	Campfire()
	{
		static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/Campfire.png");
		texture = tex;

		srect.h = 720;
		srect.w = 1280;
		srect.x = 0;

		drect.h = 720;
		drect.w = 1280;
	}
};
