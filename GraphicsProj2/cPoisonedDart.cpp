#include "cPoisonedDart.h"
#include "eTrapType.h"


TrapOrTreasure::cPoisonedDart::cPoisonedDart(): cTrap("Poisoned Dart", "A poisoned dart is thrown from the wall in direction of the loot spot")
{
	SetTheTrap();
}

void TrapOrTreasure::cPoisonedDart::SetTheTrap()
{
	this->difficulty = 13;
	this->damage = 0.1f;
	this->type = eTrapType::POISON;
}

TrapOrTreasure::cPoisonedDart::~cPoisonedDart()
{
}

bool TrapOrTreasure::cPoisonedDart::HasPickUpAwakeTheDrake()
{
	return false;
}
