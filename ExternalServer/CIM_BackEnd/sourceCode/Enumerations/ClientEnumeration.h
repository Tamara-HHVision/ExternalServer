#pragma once

namespace CIM_Backend
{
	enum class EClientType : uint8_t
	{
		EgoVehicle,
		HQClient,
		Pedestrian,
		Observer,
		MotionCapture,
		VR,
		OpenScenario,
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