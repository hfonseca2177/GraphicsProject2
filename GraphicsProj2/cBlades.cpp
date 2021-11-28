#include "cBlades.h"

TrapOrTreasure::cBlades::cBlades() : cTrap("Sharp Blades", "Sharp Blades come from different directions and cut you down, ugly...")
{
	SetTheTrap();
}

TrapOrTreasure::cBlades::~cBlades()
{
}

void TrapOrTreasure::cBlades::SetTheTrap()
{
	this->difficulty = 15;
	this->damage = 0.25f;
	this->type = eTrapType::SLASHING;
}

bool TrapOrTreasure::cBlades::HasPickUpAwakeTheDrake()
{
	return false;
}
