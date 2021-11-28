#include "cStoneHat.h"

TrapOrTreasure::cStoneHat::cStoneHat() : cTrap("Stone Hat", "A stone falls from the ceil into your head.")
{
	SetTheTrap();
}

TrapOrTreasure::cStoneHat::~cStoneHat()
{
}

void TrapOrTreasure::cStoneHat::SetTheTrap()
{
	this->difficulty = 8;
	this->damage = 0.15f;
	this->type = eTrapType::BLUDGEONING;
}

bool TrapOrTreasure::cStoneHat::HasPickUpAwakeTheDrake()
{
	return false;
}
