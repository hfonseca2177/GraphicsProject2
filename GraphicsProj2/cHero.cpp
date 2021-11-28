#include <sstream>
#include "cHero.h"

TrapOrTreasure::cHero::cHero()
{
	Reset();
}

TrapOrTreasure::cHero::~cHero()
{
	delete _mediator;
}

void TrapOrTreasure::cHero::TakeDamge(float damage)
{
	this->life -= this->life * damage;
}

void TrapOrTreasure::cHero::AddDisarmedTraps(int difficult)
{
	if (difficult > 5)
	{
		this->bonus += 1;
	}
	this->disarmedTraps += 1;
}

void TrapOrTreasure::cHero::AddLoot(int goldValue)
{
	if (goldValue > 10)
	{
		this->bonus += 1;
	}	
	this->lootCollected += 1;
	this->gold+= goldValue;
}

int TrapOrTreasure::cHero::GetBonusRoll()
{
	return this->bonus;
}

bool TrapOrTreasure::cHero::IsAlive()
{
	return this->life>0;
}

void TrapOrTreasure::cHero::SeekTreasure()
{
	this->_mediator->Notify(this, eSeekEvent::SEEK);
}

void TrapOrTreasure::cHero::TakeLethalDamage()
{
	this->life = 0;
}

std::string TrapOrTreasure::cHero::PrintStats()
{
	std::stringstream buffer;
	buffer << "| HP: " << life << " | Bonus: " << bonus << " |";
	return buffer.str();
}

std::string TrapOrTreasure::cHero::PrintScore()
{
	std::stringstream buffer;
	buffer << "| Score: " << score;
	buffer << " | Gold : " << gold;
	buffer << " | Disarmed: " << disarmedTraps;
	buffer << " | Treasure: " << lootCollected;
	return buffer.str();
}

void TrapOrTreasure::cHero::Reset()
{
	this->life = 100;
	this->bonus = 4;
	this->gold = 0;
	this->disarmedTraps = 0;
	this->lootCollected = 0;
	this->score = 0;
}
