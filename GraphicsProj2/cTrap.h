#pragma once
#include <string>
#include "cLootable.h"
#include "eTrapType.h"

namespace TrapOrTreasure
{
	//Base trap class used to cause damage to the player and pehaps trigger the drake
	class cTrap: public cLootable
	{
	protected:
		//Trap difficult class number
		int difficulty;
		//In Percentage
		float damage;
		//Trap type
		eTrapType type;

	public:
		cTrap(std::string _name, std::string _description);
		virtual ~cTrap();
		//Prepare the trap
		virtual void SetTheTrap();
		//Try to disarm the trap
		virtual bool TryToDisarm(int heroRoll); 
		//Return the dmg taken
		virtual float GetDamage();
		//Each specific treasure must implement it
		virtual bool HasPickUpAwakeTheDrake()=0;
		//Return the trap type
		eTrapType GetType();
		//Returns the trap difficult
		virtual int GetDifficulty();
	};
};