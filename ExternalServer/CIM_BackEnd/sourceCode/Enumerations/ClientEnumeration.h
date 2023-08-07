#pragma once

namespace CIM_Backend
{
	enum class EClientType : uint8_t
	{
		EgoVehicle,
		Pedestrian,
		VR,
		ControlCenter,
		OpenScenario,
		HQClient,
		Observer,
		MotionCapture,
		TrafficSystem,
	};

	enum class ECharacterSelection :uint8_t
	{
		UE4MannequinFemale,
		UE4MannequinMale,
		Alex,
		Faye,
		Juliette
	};


	enum class ETrafficCarType :uint8_t
	{
		TeslaModelX,
		NavyaPeopleMover
	};
}