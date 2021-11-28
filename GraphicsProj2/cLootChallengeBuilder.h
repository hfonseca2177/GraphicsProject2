#pragma once

#include "cTreasure.h"
#include "cTrap.h"
#include "cTreasureFactory.h"

namespace TrapOrTreasure
{
	//Set of Loot and Trap
	struct sLootChallenge
	{
		cTreasure* treasure;
		cTrap* trap;
	};

	//Build and return a LootChallenge 
	//==============================================
	/*
	[Patterns]: Builder to Assemble the combination of Trap and Treasure for a seek round
	[Improvement reflex]: This builder contains the Trap and Treasure Factories and abstracts the challenge 
	Generation 
	*/
	//==============================================
	class cLootChallengeBuilder
	{
	private:
		//treasure factory needs to be instantiated and trap one, just call the singleton method GetInstance()
		cTreasureFactory* treasureFactory;
	public:
		cLootChallengeBuilder();
		virtual ~cLootChallengeBuilder();
		sLootChallenge GetChallenge();
	};
}

