#pragma once
#include <string>
#include "cTreasure.h"

namespace TrapOrTreasure
{
	//Handfull of coins
	class cGoldCoins : public cTreasure
	{
	public:
		cGoldCoins(int amount);
		virtual ~cGoldCoins();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
