#include "cTrapFactory.h"
#include "cTrap.h"
#include "cPoisonedDart.h"
#include "cSpear.h"
#include "cPetrify.h"
#include "cFireBreath.h"
#include "cStoneHat.h"
#include "cShockWave.h"
#include "cBlades.h"

static TrapOrTreasure::cTrapFactory* _instance = nullptr;

//Returns a Unique instance of trapFactory
TrapOrTreasure::cTrapFactory* TrapOrTreasure::cTrapFactory::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new cTrapFactory();
	}
	return _instance;
}

TrapOrTreasure::cTrapFactory::~cTrapFactory()
{
	std::map<eTrapType, cTrap*>::iterator it;
	for (it = this->trapPool.begin();
		it != this->trapPool.end();
		++it) {
		delete it->second;
	}
	this->trapPool.clear();
	delete _instance;
}

TrapOrTreasure::cTrap* TrapOrTreasure::cTrapFactory::GetTrapByType(eTrapType type)
{
	cTrap* trap = nullptr;
	trap = this->trapPool[type];

	switch (type)
	{
	case eTrapType::POISON:
	{
		if (trap == nullptr)
		{
			trap = new cPoisonedDart();
			this->trapPool.insert(std::make_pair(type, trap));
		}
		break;
	}
	case eTrapType::BLUDGEONING:
		if (trap == nullptr)
		{
			trap = new cStoneHat();
			this->trapPool.insert(std::make_pair(type, trap));
		}
		break;
	case eTrapType::MAGIC:
		if (trap == nullptr)
		{
			trap = new cPetrify();
			this->trapPool.insert(std::make_pair(type, trap));
		}
		break;
	case eTrapType::ELECTRIC:
		if (trap == nullptr)
		{
			trap = new cShockWave();
			this->trapPool.insert(std::make_pair(type, trap));
		}
		break;
	case eTrapType::FIRE:
		if (trap == nullptr)
		{
			trap = new cFireBreath();
			this->trapPool.insert(std::make_pair(type, trap));
		}
		break;
	case eTrapType::SLASHING:
		if (trap == nullptr)
		{
			trap = new cBlades();
			this->trapPool.insert(std::make_pair(type, trap));
		}
		break;
	default:
		{//PIERCING as default
			if (trap == nullptr)
			{
				trap = new cSpear();
				this->trapPool.insert(std::make_pair(type, trap));
			}
			break;
		}
		
	}
	
	return trap;
}


