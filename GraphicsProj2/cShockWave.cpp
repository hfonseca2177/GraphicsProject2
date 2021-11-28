#include "cShockWave.h"

TrapOrTreasure::cShockWave::cShockWave() : cTrap("Shock Wave", "You lose control of your body and gets electrified for 5 sec")
{
	SetTheTrap();
}

TrapOrTreasure::cShockWave::~cShockWave()
{
}

void TrapOrTreasure::cShockWave::SetTheTrap()
{
	this->difficulty = 13;
	this->damage = 0.35f;
	this->type = eTrapType::ELECTRIC;
}

bool TrapOrTreasure::cShockWave::HasPickUpAwakeTheDrake()
{
	return true;
}
