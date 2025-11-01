#pragma once
#include <iostream>
#include "Entity.h"

class Player : public Entity
{
	private:
		int statPoints = 4;
		int level = 1;
		int xp = 0;
		int xpToNextLevel = 100;
		std::string characterClass = "";

	public:
		Player()
		{

		}
		Player(int MaxHealth, int Strength, int Agility, int Luck) : Entity()
		{
			Entity::setMaxHealth(MaxHealth);
			Entity::setHealth(MaxHealth);
			Entity::setStrength(Strength);
			Entity::setAgility(Agility);
			Entity::setLuck(Luck);
		}
		void gainXp(int xpGained)
		{
			xp += xpGained;
			if (xp >= xpToNextLevel)
			{
				level++;
				xp -= xpToNextLevel;
				statPoints += 2;
				float e = exp(1);
				xpToNextLevel = 99 + (pow(level, exp(1)));
			}
		}
		int getStatPoints()
		{
			return statPoints;
		}
		void setStatPoints(int value)
		{
			statPoints = value;
		}
		int getLevel()
		{
			return level;
		}
		void setLevel(int value)
		{
			level = value;
		}
		int getXp()
		{
			return xp;
		}
		void setXp(int value)
		{
			xp = value;
		}
		int getXpToNextLevel()
		{
			return xpToNextLevel;
		}
		void setXpToNextLevel(int value)
		{
			xpToNextLevel = value;
		}
		std::string getCharacterClass()
		{
			return characterClass;
		}
		std::string setCharacterClass(std::string value)
		{
			return characterClass = value;
		}
};