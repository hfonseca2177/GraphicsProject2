#pragma once
#include "IRoll.h"

namespace RollSystem
{
	//Utility To return a ranom FlipCoin Decision
	enum class eCoinSide
	{
		HEAD, TAIL
	};
	class cFlipCoinUtils
	{
	private:
		void Init();
	public:
		cFlipCoinUtils();
		virtual ~cFlipCoinUtils();
		// Flips the coin
		eCoinSide FlipCoin();
		
	};

}
