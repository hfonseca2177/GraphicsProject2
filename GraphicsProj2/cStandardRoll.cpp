#include "cStandardRoll.h"
#include <time.h>
#include <cstdlib>

struct sD20
{
	const int min = 1;
	const int max = 20;
};

const sD20 d20;

void RollSystem::cStandardRoll::Init()
{
	//seed the random
	unsigned int uiTime = static_cast<unsigned int>(time(NULL));	
	srand(uiTime);
}

RollSystem::cStandardRoll::cStandardRoll()
{
	Init();
}

RollSystem::cStandardRoll::~cStandardRoll()
{
}

int RollSystem::cStandardRoll::GetRandom(int low, int high)
{
	return low + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX) / (high - low));
}

int RollSystem::cStandardRoll::Roll()
{
	return GetRandom(d20.min, d20.max);
}
