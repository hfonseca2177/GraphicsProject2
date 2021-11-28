#pragma once


namespace TrapOrTreasure
{
	class IGameAgent;

	//Seek game events
	enum class eSeekEvent
	{
		SEEK, DRAKE_AWAKE, TRAP_FOUND,TRAP_DISARMED,TRAP_FAILED,TREASURE_FOUND, HERO_DEAD
	};
	//Mediator Interface for Game Agents
	class ISeekForTreasureMediator
	{
	public:
		virtual void Notify(IGameAgent* gameAgent, const eSeekEvent seekEvent)=0;
	};
}

