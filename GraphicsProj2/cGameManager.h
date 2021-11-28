#pragma once
#include <vector>
#include "cModel.h"
#include "sGameStatus.h"

namespace TrapOrTreasure
{
	//Game manager that executes the game logic and orchestration
	//==============================================
	/*
	[Patterns]: Singleton - Only one Game Manager instance to keep the state of the game
	
	[Improvement reflex]: Multiple instances could cause inconsistent state of the game
	*/
	//==============================================
	class cGameManager
	{
	private:
		cGameManager() {};
	public:
		cGameManager(cGameManager& other) = delete;
		void operator=(const cGameManager&) = delete;
		virtual ~cGameManager();
		static cGameManager *GetInstance();
		void StartGame();
		void SetModels(std::vector<cModel*> &_models);
		void SearchForTreasure();
		void DidYouAwakeTheDrake();
		sGameStatus GetStatus();
	};

	
}
