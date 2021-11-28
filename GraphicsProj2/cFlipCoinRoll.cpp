#include "cFlipCoinUtils.h"
#include "cStandardRoll.h"

RollSystem::cStandardRoll* randomGenerator;

void RollSystem::cFlipCoinUtils::Init()
{
	randomGenerator = new RollSystem::cStandardRoll();
}

RollSystem::cFlipCoinUtils::cFlipCoinUtils()
{
	Init();
}

RollSystem::cFlipCoinUtils::~cFlipCoinUtils()
{
	delete randomGenerator;
}

RollSystem::eCoinSide RollSystem::cFlipCoinUtils::FlipCoin()
{
	RollSystem::eCoinSide flipResult;

	int roll = randomGenerator->GetRandom(1, 1000);
	if (roll % 2 == 0)
	{
		flipResult = eCoinSide::HEAD;
	}
	else {
		flipResult = eCoinSide::TAIL;
	}
	return flipResult;
}
