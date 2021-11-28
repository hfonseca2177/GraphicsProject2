#include "cPetrify.h"

TrapOrTreasure::cPetrify::cPetrify() : cTrap("Petrify", "After you touch it you start becoming a stone")
{
	SetTheTrap();
}

TrapOrTreasure::cPetrify::~cPetrify()
{
}

void TrapOrTreasure::cPetrify::SetTheTrap()
{
	this->difficulty = 12;
	this->damage = 0.7f;
	this->type = eTrapType::MAGIC;
}

bool TrapOrTreasure::cPetrify::HasPickUpAwakeTheDrake()
{
	return false;
}
