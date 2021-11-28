#include<iostream>
#include <glm/glm.hpp>
#include <sstream>
#include "cGameManager.h"
#include "ISeekForTreasureMediator.h"
#include "cSeekForTreasureMediator.h"
#include "cHero.h"
#include "cDragon.h"
#include "cDragonsLair.h"


using namespace TrapOrTreasure;

static cGameManager* _instance = nullptr;
cSeekForTreasureMediator* mediator;
cHero* hero;
cDragon* dragon;
cDragonsLair* lair;
std::vector<cModel*> lootableModels;
cModel* dragonModel = nullptr;
sGameStatus gameStatus;
int lootableIndex = 0;
const glm::vec3 successLootedColor = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 failLootedColor = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 notLootedColor = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 normalDragonColor = glm::vec3(0.319f, 0.167f, 0.365f);
const glm::vec3 enragedDragonColor = glm::vec3(1.0f, 0.064f, 0.0f);
bool gameOver = false;

void SetGameStatus(cHero* hero, string lairLabel, string lootable, string message, int totalLoot, int lootCount)
{
	gameStatus.heroStats = hero->PrintStats();
	gameStatus.heroScore = hero->PrintScore();
	gameStatus.currentLairItem = "Seeking Treasure on " + lairLabel;
	gameStatus.lootableFound = "Found: " + lootable;
	stringstream lootsRemainingBuffer;
	lootsRemainingBuffer << "Loot:" << lootCount << "/" << totalLoot;
	gameStatus.lootsRemaining = lootsRemainingBuffer.str();
	gameStatus.result = message;
}

void ResetGame()
{
	for (size_t i = 0; i < lootableModels.size(); i++)
	{
		cModel* m = lootableModels[i];
		m->SetLooted(false);
		m->GetMesh()->SetColor(notLootedColor);
	}
	gameOver = false;
	hero->Reset();
	dragonModel->GetMesh()->SetColor(normalDragonColor);
	lootableIndex = 0;
	SetGameStatus(hero, lootableModels[lootableIndex]->GetLairLabel(), "", "Restarting the game...", lootableModels.size(), lootableIndex+1);
}

void CheckGameOver()
{
	bool noMoreLoot = lootableIndex >= lootableModels.size();
	gameOver = !hero->IsAlive() || noMoreLoot;

	if (gameOver)
	{
		if (hero->IsAlive())
		{
			SetGameStatus(hero, "Congratulations!!!", "Fortune!", "YOU WON!", lootableModels.size(), lootableIndex + 1);
		}
		else
		{
			SetGameStatus(hero, "Sorry!!!", "Shame!", "YOU LOSE!", lootableModels.size(), lootableIndex + 1);
		}
	}
}


void GameCallback(eSeekEvent seekEvent, std::string lootableDesc)
{
	switch (seekEvent)
	{
	case eSeekEvent::TRAP_FOUND:
	{
		CheckGameOver();
		if (gameOver)
		{
			break;
		}
		std::cout << "TRAP FOUND" << std::endl;
		lootableModels[lootableIndex]->GetMesh()->SetColor(successLootedColor);
		SetGameStatus(hero, lootableModels[lootableIndex]->GetLairLabel(), lootableDesc, "It's a Trap!!!", lootableModels.size(), lootableIndex+1);
		
		break;
	}
	case eSeekEvent::TRAP_FAILED:
	{
		CheckGameOver();
		if (gameOver)
		{
			break;
		}
		std::cout << "TRAP FAILED" << std::endl;
		lootableModels[lootableIndex]->GetMesh()->SetColor(failLootedColor);
		SetGameStatus(hero, lootableModels[lootableIndex]->GetLairLabel(), lootableDesc, "F@#*! It Hurts :(", lootableModels.size(),lootableIndex+1);
		break;
	}
	case eSeekEvent::TREASURE_FOUND:
	{
		CheckGameOver();
		if (gameOver)
		{
			break;
		}
		std::cout << "TREASURE FOUND" << std::endl;
		lootableModels[lootableIndex]->GetMesh()->SetColor(successLootedColor);
		SetGameStatus(hero, lootableModels[lootableIndex]->GetLairLabel(), lootableDesc, "Money, money, money !!!", lootableModels.size(), lootableIndex+1);
		
		break;
	}
	case eSeekEvent::DRAKE_AWAKE:
	{
		std::cout << "DRAKE_AWAKE" << std::endl;
		cGameManager::GetInstance()->DidYouAwakeTheDrake();
		dragonModel->GetMesh()->SetColor(enragedDragonColor);
		SetGameStatus(hero, lootableModels[lootableIndex]->GetLairLabel(), lootableDesc, "ROWARRRRRRRRR!!!", lootableModels.size(), lootableIndex+1);
		break;
	}
	case eSeekEvent::HERO_DEAD:
	{
		std::cout << "HERO DEAD!" << std::endl;
		SetGameStatus(hero, lootableModels[lootableIndex]->GetLairLabel(), lootableDesc, "Goodbye cruel world...", lootableModels.size(), lootableIndex+1);
		break;
	}
	default:
		break;
	}
}

cGameManager* cGameManager::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new cGameManager();
	}
	return _instance;
}

void TrapOrTreasure::cGameManager::StartGame()
{
	hero = new cHero();
	lair = new cDragonsLair();
	dragon = new cDragon();
	mediator = new cSeekForTreasureMediator(hero, lair, dragon);
	void(*callback)(TrapOrTreasure::eSeekEvent, std::string);
	callback = &GameCallback;
	mediator->SetGameManagerCallback(callback);
	for (size_t i = 0; i < lootableModels.size(); i++)
	{
		cModel* m = lootableModels[i];
		m->SetLooted(false);
		m->GetMesh()->SetColor(notLootedColor);
	}
	lootableIndex = 0;
	SetGameStatus(hero, lootableModels[lootableIndex]->GetLairLabel(), "", "Starting...", lootableModels.size(), lootableIndex+1);	
}

void TrapOrTreasure::cGameManager::SetModels(std::vector<cModel*> &_models)
{
	for (size_t i = 0; i < _models.size(); i++)
	{
		cModel* m = _models[i];
		if (m->IsLootable())
		{
			m->GetMesh()->SetColor(notLootedColor);
			lootableModels.push_back(m);
		}
		else if(m->GetLairLabel() =="Dragon")
		{
			dragonModel = m;
			dragonModel->GetMesh()->SetColor(normalDragonColor);
		}
	}
}

cGameManager::~cGameManager()
{
	delete _instance;
}

void cGameManager::SearchForTreasure()
{
	if (gameOver)
	{
		ResetGame();
	}
	else
	{
		hero->SeekTreasure();
		lootableIndex++;
	}
}

void cGameManager::DidYouAwakeTheDrake()
{
	dragonModel->GetMesh()->SetColor(enragedDragonColor);
}

sGameStatus TrapOrTreasure::cGameManager::GetStatus()
{
	return gameStatus;
}
