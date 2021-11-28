#include "cGoldCoins.h"

TrapOrTreasure::cGoldCoins::cGoldCoins(int amount) : TrapOrTreasure::cTreasure("Gold coins", "Bunch of Gold Coins", amount) {}
TrapOrTreasure::cGoldCoins::~cGoldCoins()
{
}
bool TrapOrTreasure::cGoldCoins::HasPickUpAwakeTheDrake()
{
	bool awake = (this->goldValue > 300);
	return awake;
}
;