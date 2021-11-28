#pragma once
#include "cTrap.h"

namespace TrapOrTreasure
{
	//Trap that throws a fire flame at the player
	class cFireBreath : public cTrap
	{
	public:
		cFireBreath();
		virtual ~cFireBreath();
		virtual void SetTheTrap();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
