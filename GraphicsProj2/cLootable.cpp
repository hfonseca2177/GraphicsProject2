#include "cLootable.h"

TrapOrTreasure::cLootable::cLootable():cLootable("Stone", "Worthless stone piece")
{	
}
TrapOrTreasure::cLootable::cLootable(std::string _name, std::string _description)
{
	this->name = _name;
	this->description = _description;
}
TrapOrTreasure::cLootable::~cLootable() 
{
}
std::string TrapOrTreasure::cLootable::GetName()
{
	return this->name;
}
std::string TrapOrTreasure::cLootable::GetDescription()
{
	return this->description;
}