#pragma once
#include <string>
#include "cTreasure.h"

namespace TrapOrTreasure
{
	//Beautiful  king's crown
	class cKingsCrown : public cTreasure
	{
	public:
		cKingsCrown();
		virtual ~cKingsCrown();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
