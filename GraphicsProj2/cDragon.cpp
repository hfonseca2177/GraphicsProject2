#include "cDragon.h"
#include "cFlipCoinUtils.h"

TrapOrTreasure::cDragon::cDragon()
{
	this->flipCoinUtil = new RollSystem::cFlipCoinUtils();
}

TrapOrTreasure::cDragon::~cDragon()
{
	delete this->flipCoinUtil;
}

void TrapOrTreasure::cDragon::DidTheDrakeAwake()
{
	if (this->flipCoinUtil->FlipCoin() == RollSystem::eCoinSide::HEAD)
	{
		this->_mediator->Notify(this, TrapOrTreasure::eSeekEvent::DRAKE_AWAKE);
	}
}
