#pragma once
#include <string>
#include "IGameAgent.h"

namespace TrapOrTreasure
{
	//Hero class that contain the player stats and score
	class cHero : public IGameAgent
	{
	private:
		int life;
		int gold;
		int score;
		int disarmedTraps;
		int lootCollected;
		int bonus;
	public:
		cHero();
		virtual ~cHero();
		//Calculate the damage dealt
		void TakeDamge(float damage);
		//Add the trap difficult to score
		void AddDisarmedTraps(int difficult);
		//Add loot to the scoore
		void AddLoot(int goldValue);
		//Return the bonus to be added to hero rolls
		int GetBonusRoll();
		//Verifies if is still alive
		bool IsAlive();
		//Proceed with the seek
		void SeekTreasure();
		//Get hit by the dragon and takes lethal damage
		void TakeLethalDamage();
		//Show Hero Stats
		std::string PrintStats();
		//Show Hero score
		std::string PrintScore();
		//Reset the stats and score
		void Reset();
	};
}
