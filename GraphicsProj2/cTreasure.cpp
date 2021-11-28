#include "cTreasure.h"

TrapOrTreasure::cTreasure::cTreasure(std::string _name, std::string _description, int _goldValue):cLootable(_name, _description)
{
	this->goldValue = _goldValue;
}

TrapOrTreasure::cTreasure::~cTreasure()
{
}

int TrapOrTreasure::cTreasure::ValueInGold()
{
	return this->goldValue;
}

bool TrapOrTreasure::cTreasure::HasPickUpAwakeTheDrake()
{
	//Defaut implementation doesnt awake the drake
	return false;
}
