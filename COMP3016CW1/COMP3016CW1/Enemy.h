#pragma once
#include "Entity.h"

class Enemy : public Entity
{
	private:
		int giveXp = 0;
		std::string name = "";

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
};