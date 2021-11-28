#include  "cRollSystem.h"
#include "cStandardRoll.h"
#include "cFlipCoinUtils.h"
#include "cD6StrategyRoll.h"

namespace RollSystem
{
	//Pimpl responsible for RollSystem Implementation
	//============================================================================
	/*
	[Patterns]: PImpl for the roll system 
	[Improvement reflex]: I can change the impl used here to use only one from Standard and d6 Impls or even
	 switch between them like I did
	*/
	//============================================================================
	class cRollSystem::Impl
	{
	private:
		cFlipCoinUtils* flipCoinUtils;
		IRoll* generatorA;
		IRoll* generatorB;
	public:
		int Roll() {
			eCoinSide result = flipCoinUtils->FlipCoin();
			if (result == eCoinSide::HEAD)
			{
				return generatorA->Roll();
			}else
			{
				return generatorB->Roll();
			}
		}

		void Init()
		{
			flipCoinUtils = new cFlipCoinUtils();
			generatorA = new cStandardRoll();
			generatorB = new cD6StrategyRoll();
		}
		~Impl()
		{
			delete flipCoinUtils, generatorA, generatorB;
		}
	};

	

	cRollSystem::cRollSystem()
		: pimpl{ std::make_unique<Impl>() }
	{
		pimpl->Init();
	}
	cRollSystem::~cRollSystem() = default;
	int cRollSystem::Roll()
	{
		return pimpl->Roll();
	}
}
