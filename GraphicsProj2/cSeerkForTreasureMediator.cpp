#include "cSeekForTreasureMediator.h"

TrapOrTreasure::cSeekForTreasureMediator::~cSeekForTreasureMediator()
{
	delete hero, lair, dragon;
}

void TrapOrTreasure::cSeekForTreasureMediator::Notify(IGameAgent* gameAgent, const eSeekEvent seekEvent)
{
	switch (seekEvent)
	{
	case eSeekEvent::SEEK:
	{
		//Generate a challenge
		sLootChallenge challenge = this->lair->ChallengeHero();
		//Luck check if found a trap or treasure
		if (RollSystem::eCoinSide::HEAD == this->flipCoinUtil->FlipCoin())
		{
			gmCallback(TrapOrTreasure::eSeekEvent::TRAP_FOUND, challenge.trap->GetDescription());
			//Hero main  roll to avoid damage by disarming the trap and getting its loot
			int heroRoll = this->rollSystem->Roll() + hero->GetBonusRoll();
			//attempt to disarm
			bool disarmed = challenge.trap->TryToDisarm(heroRoll);
			if (disarmed)
			{
				gmCallback(TrapOrTreasure::eSeekEvent::TRAP_DISARMED, challenge.trap->GetDescription());
				//If disarme , score it 
				hero->AddDisarmedTraps(challenge.trap->GetDifficulty());
				hero->AddLoot(challenge.treasure->ValueInGold());
				gmCallback(TrapOrTreasure::eSeekEvent::TREASURE_FOUND, challenge.treasure->GetDescription());
				//check if picking up the treasure awakes the drake
				if (challenge.treasure->HasPickUpAwakeTheDrake())
				{
					dragon->DidTheDrakeAwake();
				}
			}
			else
			{
				gmCallback(TrapOrTreasure::eSeekEvent::TRAP_FAILED, challenge.trap->GetDescription());
				//If failed, takes damage
				hero->TakeDamge(challenge.trap->GetDamage());
				//check if springing the trap awakes the drake
				if (challenge.trap->HasPickUpAwakeTheDrake())
				{
					dragon->DidTheDrakeAwake();
				}
			}
		}
		else
		{
			gmCallback(TrapOrTreasure::eSeekEvent::TREASURE_FOUND, challenge.treasure->GetDescription());
			hero->AddLoot(challenge.treasure->ValueInGold());
			//check if picking up the treasure awakes the drake
			if (challenge.treasure->HasPickUpAwakeTheDrake())
			{
				dragon->DidTheDrakeAwake();
			}
		}
		//Case still alive continues
		if (hero->IsAlive())
		{
			//disabled auto run
			//hero->SeekTreasure();
		}
		else {
			gmCallback(TrapOrTreasure::eSeekEvent::HERO_DEAD, challenge.trap->GetDescription());
			break;
		}
		break;
	}
	case eSeekEvent::DRAKE_AWAKE:
	{
		gmCallback(TrapOrTreasure::eSeekEvent::DRAKE_AWAKE, "Tiamat Up!");
		//Case something awakes the dragon is game over
		hero->TakeLethalDamage();
		gmCallback(TrapOrTreasure::eSeekEvent::HERO_DEAD, "The Light!");
		break;
	}
	default:
		break;
	}
}


void TrapOrTreasure::cSeekForTreasureMediator::SetGameManagerCallback(void(*callback)(TrapOrTreasure::eSeekEvent, std::string))
{
	gmCallback = callback;
}
