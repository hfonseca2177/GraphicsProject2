#pragma once
#include "cTrap.h"

namespace TrapOrTreasure
{
	//Trap that throws a poisoned dart
	class cPoisonedDart : public cTrap
	{
	public:
		cPoisonedDart();
		virtual void SetTheTrap();
		virtual ~cPoisonedDart();
		virtual bool HasPickUpAwakeTheDrake();
	};
}