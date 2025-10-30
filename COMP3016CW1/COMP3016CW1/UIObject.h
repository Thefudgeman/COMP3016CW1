#pragma once
#include "Mouse.h"
#include <SDL3/SDL_render.h>

class UIObject
{
public:
	SDL_Texture* texture;
	SDL_FRect srect, drect;
	bool isSelected = false;


public:
	UIObject()
	{

	}

	virtual ~UIObject()
	{

	}

	void draw()
	{
		SDL_RenderTexture(renderer, texture, &srect, &drect);
	}
};