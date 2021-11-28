#include "cKingsCrown.h"

TrapOrTreasure::cKingsCrown::cKingsCrown() : TrapOrTreasure::cTreasure("King's crown", "A marvelous king's crown! Holy Moly!", 5000) {}
TrapOrTreasure::cKingsCrown::~cKingsCrown()
{
}
bool TrapOrTreasure::cKingsCrown::HasPickUpAwakeTheDrake()
{
	return true;
}
;