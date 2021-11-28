#include "cSpear.h"

TrapOrTreasure::cSpear::cSpear():cTrap("Spear", "A spear comes from bellow")
{
	SetTheTrap();
}

TrapOrTreasure::cSpear::~cSpear()
{
}

void TrapOrTreasure::cSpear::SetTheTrap()
{
	this->difficulty = 5;
	this->damage = 0.15f;
	this->type = eTrapType::PIERCING;
}

bool TrapOrTreasure::cSpear::HasPickUpAwakeTheDrake()
{
	return true;
}