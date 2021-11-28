#pragma once
#include <string>
#include "cTreasure.h"

namespace TrapOrTreasure
{
	//Handfull of gems
	class cGems : public cTreasure
	{
	public:
		cGems(int valueInGold);
		virtual ~cGems();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
