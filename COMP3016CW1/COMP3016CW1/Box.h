#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "Globals.h"
#include "UIObject.h"

class Box : public UIObject
{
	public:
		Box()
		{
			static SDL_Texture* tex = IMG_LoadTexture(renderer, "images/Box2.png");
			texture = tex;
			srect.h = 680;
			srect.w = 600;
			srect.x = 0;

			drect.h = 680;
			drect.w = 600;
		}
};