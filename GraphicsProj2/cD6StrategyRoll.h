#pragma once
#include "IRoll.h"


namespace RollSystem
{
	//Utility to generate pseudo random number but with d6 approach
	class cD6StrategyRoll: public IRoll
	{
	private:
		void Init();
	public:
		cD6StrategyRoll();
		virtual ~cD6StrategyRoll();
		// Return the uniform dist roll impl
		int Roll();
	};

}