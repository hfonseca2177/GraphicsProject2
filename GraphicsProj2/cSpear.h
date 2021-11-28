#pragma once
#include "cTrap.h"

namespace TrapOrTreasure
{
	//Piercing spear hits from below
	class cSpear : public cTrap
	{
	public:
		cSpear();
		virtual ~cSpear();
		virtual void SetTheTrap();
		virtual bool HasPickUpAwakeTheDrake();
	};
}