#pragma once
#include "cTrap.h"

namespace TrapOrTreasure
{
	//Trap electrifies the hero for 5 sec
	class cShockWave : public cTrap
	{
	public:
		cShockWave();
		virtual ~cShockWave();
		virtual void SetTheTrap();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
