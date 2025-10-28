#pragma once
#include "Entity.h"

class Enemy : public Entity
{
	private:
		int giveXp = 0;
		std::string name = "";
		SDL_Texture* texture;
		SDL_FRect srect, drect;

	public:
		Enemy()
		{

		}
		Enemy(int MaxHealth, int Strength, int Agility, int Luck, int GiveXp, std::string Name) : Entity()
		{
			Entity::setMaxHealth(MaxHealth);
			Entity::setHealth(MaxHealth);
			Entity::setStrength(Strength);
			Entity::setAgility(Agility);
			Entity::setLuck(Luck);
			giveXp = GiveXp;
			name = Name;
			Name = "images/Enemies/" + Name + ".png";
			SDL_Texture* tex = IMG_LoadTexture(renderer, Name.c_str());
			texture = tex;

			srect.h = 488;
			srect.w = 800;
			srect.x = 0;

			drect.h = 448;
			drect.w = 800;
		}

		int getGiveXp()
		{
			return giveXp;
		}
		
		int setGiveXp(int value)
		{
			giveXp = value;
		}

		std::string getName()
		{
			return name;
		}

		void draw()
		{
			SDL_RenderTexture(renderer, texture, &srect, &drect);
		}
};