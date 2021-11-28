#include "cDragonsLair.h"
#include "cLootChallengeBuilder.h"

TrapOrTreasure::cDragonsLair::cDragonsLair()
{
	this->challengeBuilder = new cLootChallengeBuilder();
}

TrapOrTreasure::cDragonsLair::~cDragonsLair()
{
	delete this->challengeBuilder;
}

TrapOrTreasure::sLootChallenge TrapOrTreasure::cDragonsLair::ChallengeHero()
{
	return this->challengeBuilder->GetChallenge();
}
