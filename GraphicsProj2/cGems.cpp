#include "cGems.h"

TrapOrTreasure::cGems::cGems(int valueInGold) : TrapOrTreasure::cTreasure("Shining Gems", "Handfull of shining gems", valueInGold) {}
TrapOrTreasure::cGems::~cGems()
{
}
bool TrapOrTreasure::cGems::HasPickUpAwakeTheDrake()
{
	return false;
}
;