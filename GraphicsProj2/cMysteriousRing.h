#pragma once
#include <string>
#include "cTreasure.h"

namespace TrapOrTreasure
{
	//Mysterious gold ring with some inscriptions
	class cMysteriousRing : public cTreasure
	{
	public:
		cMysteriousRing();
		virtual ~cMysteriousRing();
		virtual bool HasPickUpAwakeTheDrake();
	};
}
