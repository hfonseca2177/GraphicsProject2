#pragma once
#include "ISeekForTreasureMediator.h"
#include "cHero.h"
#include "cDragonsLair.h"
#include "cDragon.h"
#include "cRollSystem.h"
#include "cFlipCoinUtils.h"

namespace TrapOrTreasure
{
	//Seek treasure events Mediator between game agents
	//==============================================
	/*
	[Patterns]: Mediator
	[Improvement reflex]: Through this mediator, I could Isolate all the 3 game agents, the hero, lair and dragon 
	does not have to know about each other implementations but they are able to interact throughout the mediator
	*/
	//==============================================

	class cSeekForTreasureMediator : public ISeekForTreasureMediator
	{
	private:
		cHero* hero;
		cDragonsLair* lair;
		cDragon* dragon;
		RollSystem::cRollSystem* rollSystem;
		RollSystem::cFlipCoinUtils* flipCoinUtil;
		void (*gmCallback)(TrapOrTreasure::eSeekEvent, std::string lootableDesc) = nullptr;
	
	public:
		cSeekForTreasureMediator(cHero* _hero, cDragonsLair* _lair, cDragon* _dragon) : hero(_hero), lair(_lair), dragon(_dragon){
			hero->SetMediator(this);
			lair->SetMediator(this);
			dragon->SetMediator(this);
			rollSystem = new RollSystem::cRollSystem();
			flipCoinUtil = new RollSystem::cFlipCoinUtils();
		}
		virtual ~cSeekForTreasureMediator();
		virtual void Notify(IGameAgent* gameAgent, const eSeekEvent seekEvent);
		void SetGameManagerCallback(void (*callback)(TrapOrTreasure::eSeekEvent, std::string));
	};
}

