#pragma once
#include <string>
#include "cLootable.h"

namespace TrapOrTreasure
{
	//Treasure base representation 
	class cTreasure : public cLootable
	{
	protected:
		int goldValue;
		cTreasure(std::string _name, std::string _description, int _goldValue);
	public:
		virtual ~cTreasure();
		virtual int ValueInGold();
		//Each specific treasure must implement it
		virtual bool HasPickUpAwakeTheDrake()=0;
	};
}
