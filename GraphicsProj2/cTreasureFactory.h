#pragma once
#include "cTreasure.h"
#include <vector>
#include "cStandardRoll.h"

namespace TrapOrTreasure
{
	// Create random treasure items to be lootable
	//==============================================
	/*
	[Patterns]: Sort of Dynamic Factory + Builder since it also assembles different treasure instances
	based on random factors
	[Improvement reflex]: if not done, I would have to spread treasure logic across the main method or other classes, 
	And would lose a lot of randonmness of treasure result 
	*/
	//==============================================
	class cTreasureFactory
	{
	private:
		std::vector<cTreasure*> hoard;
		RollSystem::cStandardRoll* randomGenerator;
		//Instantiate random Treasure for the session
		void InitTheHoard();
	public:
		//Constructor
		cTreasureFactory();
		//Desctructor
		virtual ~cTreasureFactory();
		//Get one treasure instance
		cTreasure* GetTreasure();
	};
}
