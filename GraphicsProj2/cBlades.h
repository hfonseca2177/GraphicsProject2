#pragma once
#include "cTrap.h"

namespace TrapOrTreasure
{
	//Trap triggers blades
	class cBlades : public cTrap
	{
	public:
		cBlades();
		virtual ~cBlades();
		virtual void SetTheTrap();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
