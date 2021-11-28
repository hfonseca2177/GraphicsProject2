#include "cTrap.h"


TrapOrTreasure::cTrap::cTrap(std::string _name, std::string _description): cLootable(_name, _description)
{
	SetTheTrap();
}

TrapOrTreasure::cTrap::~cTrap()
{
}

void TrapOrTreasure::cTrap::SetTheTrap()
{
}

bool TrapOrTreasure::cTrap::TryToDisarm(int heroRoll)
{
	return heroRoll > this->difficulty;
}

float TrapOrTreasure::cTrap::GetDamage()
{
	return this->damage;
}

eTrapType TrapOrTreasure::cTrap::GetType()
{
	return this->type;
}

int TrapOrTreasure::cTrap::GetDifficulty()
{
	return this->difficulty;
}

