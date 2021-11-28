#pragma once
#include "cTrap.h"

namespace TrapOrTreasure
{
	//Trap that petrifies the player
	class cPetrify : public cTrap
	{
	public:
		cPetrify();
		virtual ~cPetrify();
		virtual void SetTheTrap();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
