#pragma once
#include <string>
#include "IAwakeTheDrake.h"

namespace TrapOrTreasure
{
	//Represents everything that is interactable to the player
	//Which means could be a treasure subclass or a trap subclass
	class cLootable: public IAwakeTheDrake
	{
	protected:
		std::string name;
		std::string description;
	public:
		cLootable();
		cLootable(std::string _name, std::string _description);
		virtual ~cLootable();
		std::string GetName();
		std::string GetDescription();
		virtual bool HasPickUpAwakeTheDrake()=0;
	};
}