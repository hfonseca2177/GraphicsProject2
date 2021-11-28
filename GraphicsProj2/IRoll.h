#pragma once

namespace RollSystem
{
	//Interface for the Roll System used in the game
	class IRoll
	{
	public:
		IRoll() {};
		virtual ~IRoll(){};
		//Returns a random number used to make dicisions on the game
		virtual int Roll()=0;
	};
}
