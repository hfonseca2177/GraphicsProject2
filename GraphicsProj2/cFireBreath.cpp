#include "cFireBreath.h"

TrapOrTreasure::cFireBreath::cFireBreath() : cTrap("Fire Breath", "A burst of Flame comes in your face...")
{
	SetTheTrap();
}

TrapOrTreasure::cFireBreath::~cFireBreath()
{
}

void TrapOrTreasure::cFireBreath::SetTheTrap()
{
	this->difficulty = 10;
	this->damage = 0.25f;
	this->type = eTrapType::FIRE;
}

bool TrapOrTreasure::cFireBreath::HasPickUpAwakeTheDrake()
{
	return false;
}
