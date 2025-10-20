#pragma once

class Player
{
public:
	int health;
	const int maxHealth;

	Player() 
		: health{ 100 }, 
		maxHealth{ 100 } 
	{
	
	}

	int returnHealth() const
	{
		return health;
	}

	int returnMaxHealth() const
	{
		return maxHealth;
	}
};