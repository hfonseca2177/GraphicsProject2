#pragma once
#include "cTrap.h"
#include <map>
#include <string>

namespace TrapOrTreasure
{
	//Return a instance of trap based on type
	//==============================================
	/*
	[Patterns]: 
	Singleton - Only one Game Manager instance to keep trap object pool
	Factory - Factory responsible for instantiate a trap subclass based on type

	[Improvement reflex] Better control of trap pool instances and instantiation
	*/
	//==============================================
	class cTrapFactory
	{
	private:
		
		std::map<eTrapType, cTrap*> trapPool;
		cTrapFactory() {};
	public:
		cTrapFactory(cTrapFactory& other) = delete;
		void operator=(const cTrapFactory&) = delete;
		virtual ~cTrapFactory();
		static cTrapFactory *GetInstance();
		//Return a Trap from a specific type
		cTrap* GetTrapByType(eTrapType type);
	};
	
}
