#pragma once
namespace TrapOrTreasure
{
	//Interface for the Awake Drake mechanism
	class IAwakeTheDrake
	{
	public:
		IAwakeTheDrake() {};
		virtual ~IAwakeTheDrake() {};
		virtual bool HasPickUpAwakeTheDrake() = 0;
	};
}
