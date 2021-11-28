#pragma once
#include "IGameAgent.h"
#include "cLootChallengeBuilder.h"


namespace TrapOrTreasure
{
	//Game agent Dragon's Lair
	//As in D&D the dragons cove has habilities and traps set to protect the dragon
	class cDragonsLair : public IGameAgent
	{
	private:
		cLootChallengeBuilder* challengeBuilder;
	public:
		cDragonsLair();
		virtual ~cDragonsLair();
		//Return a loot challenge for the hero
		sLootChallenge ChallengeHero();
	};
}

