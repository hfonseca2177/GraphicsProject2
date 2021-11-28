#include "cMysteriousRing.h"

TrapOrTreasure::cMysteriousRing::cMysteriousRing() : TrapOrTreasure::cTreasure("Ring", "A mysterious gold ring with some inscriptions", 1000) {}
TrapOrTreasure::cMysteriousRing::~cMysteriousRing()
{
}
bool TrapOrTreasure::cMysteriousRing::HasPickUpAwakeTheDrake()
{
	return true;
}
;