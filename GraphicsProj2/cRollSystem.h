#pragma once
#include <memory>

namespace RollSystem
{
	//Number Roll System used on the program 
	//[PIMPL]
	class cRollSystem
	{
	private:
		class Impl;
		std::unique_ptr<Impl> pimpl;
	public:
		cRollSystem();
		~cRollSystem();
		int Roll();
	};
}
