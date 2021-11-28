#pragma once
#include "IGameAgent.h"
#include "cFlipCoinUtils.h"

namespace TrapOrTreasure
{
	//class that holds the dragon login
	class cDragon : public IGameAgent
	{
	private:
		RollSystem::cFlipCoinUtils* flipCoinUtil;
	public:
		cDragon();
		virtual ~cDragon();
		//After something trigger to awake the dragon, check if it happend
		void DidTheDrakeAwake();
	};
}