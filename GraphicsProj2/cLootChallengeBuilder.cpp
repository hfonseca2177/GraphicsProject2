#include "cLootChallengeBuilder.h"
#include "cStandardRoll.h"


#include <map>
#include "cTrapFactory.h"

RollSystem::cStandardRoll* randomGen = new RollSystem::cStandardRoll();
std::vector<eTrapType> types;

void InitTrapTypesRotation()
{
	types.push_back(eTrapType::BLUDGEONING);
	types.push_back(eTrapType::ELECTRIC);
	types.push_back(eTrapType::FIRE);
	types.push_back(eTrapType::MAGIC);
	types.push_back(eTrapType::PIERCING);
	types.push_back(eTrapType::POISON);
	types.push_back(eTrapType::SLASHING);
}

eTrapType RotateTrap()
{
	if (types.size() == 0)
	{
		InitTrapTypesRotation();
	}
	int index = 0;
	if (types.size() > 1)
	{
		index = randomGen->GetRandom(0, ((int)types.size())-1);
	}
	eTrapType type = types.at(index);
	types.erase(types.begin() + index);
	return type;
}

TrapOrTreasure::cLootChallengeBuilder::cLootChallengeBuilder()
{
	this->treasureFactory = new cTreasureFactory();
	InitTrapTypesRotation();
}

TrapOrTreasure::cLootChallengeBuilder::~cLootChallengeBuilder()
{
	delete this->treasureFactory;
}

TrapOrTreasure::sLootChallenge TrapOrTreasure::cLootChallengeBuilder::GetChallenge()
{
	sLootChallenge challenge = sLootChallenge();
	challenge.trap = TrapOrTreasure::cTrapFactory::GetInstance()->GetTrapByType(RotateTrap());
	challenge.treasure = this->treasureFactory->GetTreasure();
	return challenge;
}
