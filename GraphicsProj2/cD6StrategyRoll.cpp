#include "cD6StrategyRoll.h"
#include <time.h>
#include <cstdlib>

struct sD6
{
	const int min = 1;
	const int max = 6;
};

const sD6 d6;



void RollSystem::cD6StrategyRoll::Init()
{
	//seed the random
	unsigned int uiTime = static_cast<unsigned int>(time(NULL));
	srand(uiTime);
}

RollSystem::cD6StrategyRoll::cD6StrategyRoll()
{
	Init();
}

RollSystem::cD6StrategyRoll::~cD6StrategyRoll()
{
	
}

int RollSystem::cD6StrategyRoll::Roll()
{
	return d6.min + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX) / (d6.max - d6.min));
}
