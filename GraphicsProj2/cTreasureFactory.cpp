#include "cTreasureFactory.h"
#include "cGoldCoins.h"
#include "cMysteriousRing.h"
#include "cKingsCrown.h"
#include "cGems.h"
#include "cStandardRoll.h"

void TrapOrTreasure::cTreasureFactory::InitTheHoard()
{
	for (size_t i = 0; i < 5; i++)
	{
		cTreasure* gold = new cGoldCoins(randomGenerator->GetRandom(1, 600));
		this->hoard.push_back(gold);
	}
	for (size_t i = 0; i < 3; i++)
	{
		cTreasure* gems = new cGems(randomGenerator->GetRandom(50, 300));
		this->hoard.push_back(gems);
	}
	cTreasure* kingsCrown = new cKingsCrown();
	this->hoard.push_back(kingsCrown);
	cTreasure* ring = new cMysteriousRing();
	this->hoard.push_back(ring);

}

TrapOrTreasure::cTreasureFactory::cTreasureFactory()
{
	this->randomGenerator = new RollSystem::cStandardRoll();
	InitTheHoard();
}

TrapOrTreasure::cTreasureFactory::~cTreasureFactory()
{
	delete randomGenerator;
}

TrapOrTreasure::cTreasure* TrapOrTreasure::cTreasureFactory::GetTreasure()
{
	int treasureIndex = randomGenerator->GetRandom(0, this->hoard.size()-1);
	return this->hoard.at(treasureIndex);
}
