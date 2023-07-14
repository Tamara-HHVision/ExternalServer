#pragma once

namespace CIM_Backend
{
	enum class EClientPacketType : uint8_t
	{
		ClientWelcomePacket,
		PedestrinTransform,
		PedestrianAnimation,
		MocapMarkerData,
		MocapBoneData,
		EgoTransform,
		TrafficCarSpawn,
		TrafficCarData,
		VRTransform,
	};

	enum class EServerPacketType : uint8_t
	{
		ServerWelcomePacket,
		NotifyOfNewMember,
		PedestrianTransformUpdate,
		PedestrianAnimationUpdate,
		EgoTransformUpdate,
		MocapMarkerUpdate,
		MocapBoneDataUpdate,
		TrafficCarSpawnUpdate,
		TrafficCarUpdate,
		VRTransformUpdate,
		NotifyOfQuit,
		ShutdownNotification
	};
}