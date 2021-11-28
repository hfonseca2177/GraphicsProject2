#pragma once
#include "ISeekForTreasureMediator.h"

namespace TrapOrTreasure
{
	
	//Game Agents that start and receive event
	class IGameAgent
	{
	protected:
		ISeekForTreasureMediator* _mediator;
	public:
		IGameAgent(ISeekForTreasureMediator* mediator = nullptr) : _mediator(mediator) {
		}
		void SetMediator(ISeekForTreasureMediator* mediator) {
			this->_mediator = mediator;
		}
	};
}