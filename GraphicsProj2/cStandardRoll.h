#pragma once
#include "IRoll.h"

namespace RollSystem
{
	//Utility to generate pseudo random number with standard library
	class cStandardRoll: public IRoll
	{
	private:
		void Init();
	public:
		cStandardRoll();
		virtual ~cStandardRoll();
		// Generate a random number in a given range
		int GetRandom(int low, int high);
		// Return the standard roll impl
		int Roll();
	};

}

