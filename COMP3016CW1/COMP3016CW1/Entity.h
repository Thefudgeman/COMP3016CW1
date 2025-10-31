#pragma once

class Entity
{
	private:
		int maxHealth;
		int health;
		int strength;
		int agility;
		int luck;
		int healthPoints;
		int maxHealthPoints;
		int strengthPoints;

	public:
		int takeDamage(int damage, int health)
		{
			return health - damage;
		}
		int getMaxHealth()
		{
			return maxHealth;
		}
		void setMaxHealth(int value)
		{
			maxHealth = value;
		}
		int getHealth()
		{
			return health;
		}
		void setHealth(int value)
		{
			health = value;
		}
		int getMaxHealthPoints()
		{
			return maxHealthPoints;
		}
		void setMaxHealthPoints(int value)
		{
			maxHealthPoints = 100 + 23 * value;
		}
		int getStrengthPoints()
		{
			return strengthPoints;
		}
		void setStrengthPoints(int value)
		{
			strengthPoints = 15 + 6 * value;
		}
		int getHealthPoints()
		{
			return healthPoints;
		}
		void setHealthPoints(int value)
		{
			healthPoints = value;
		}
		int getStrength()
		{
			return strength;
		}
		void setStrength(int value)
		{
			strength = value;
		}
		int getAgility()
		{
			return agility;
		}
		void setAgility(int value)
		{
			agility = value;
		}
		int getLuck()
		{
			return luck;
		}
		void setLuck(int value)
		{
			luck = value;
		}

};