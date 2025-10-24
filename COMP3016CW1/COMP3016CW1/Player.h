#pragma once
#include <iostream>
#include "Entity.h"

class Player : public Entity
{
	private:
		int statPoints;
		int level;
		int xp;
		int xpToNextLevel;
		std::string characterClass;

	public:
		void gainXp(int xpGained)
		{
			xp += xpGained;
			if (xp >= xpToNextLevel)
			{
				level++;
				xp -= xpToNextLevel;
				statPoints += 2;
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
			characterClass = value;
		}
};