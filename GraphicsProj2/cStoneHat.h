#pragma once

#include "cTrap.h"

namespace TrapOrTreasure
{
	//Stone falls in player's head from ceil
	class cStoneHat : public cTrap
	{
	public:
		cStoneHat();
		virtual ~cStoneHat();
		virtual void SetTheTrap();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
