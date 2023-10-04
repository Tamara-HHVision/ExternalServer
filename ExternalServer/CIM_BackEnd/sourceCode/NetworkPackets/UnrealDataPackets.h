#pragma once
#include "ClientEnumeration.h"
#include "UnrealDataPacketTypes.h"
#include "NetworkUtilities/NetworkPacketUtils.h"

namespace CIM_Backend
{
	struct PacketVersion
	{
		uint8_t ver_major;
		uint8_t ver_minor;
	};
	static PacketVersion g_PacketVersion = { 0, 1 };

	struct HeaderDataPacket
	{
		PacketVersion packetVersion;
		uint8_t type;
		uint8_t id;
	};


	// Client Packet
	struct ClientWelcomePacket
	{
		uint8_t clientType;
		int clientPort;
	};


	//Client Transform Packet
	struct PedestrianTransformPacket
	{
		UnrealTypesEmulator::Vector3D location;
		UnrealTypesEmulator::Rotator3D rotation;
	};


	struct VR_ClientTransformPacket
	{
		UnrealTypesEmulator::Vector3D bodyLocation;
		UnrealTypesEmulator::Rotator3D bodyRotation;

		UnrealTypesEmulator::Vector3D leftHandLocation;
		UnrealTypesEmulator::Rotator3D leftHandbodyRotation;
		
		UnrealTypesEmulator::Vector3D rightHandbodyLocation;
		UnrealTypesEmulator::Rotator3D rightHandbodyRotation;
	};

	struct EgoCarTransformPacket // A Packet Struct holding Car Transfrom Representation according to the "Five Body Model"
	{
		UnrealTypesEmulator::Vector3D frTireLoc;
		UnrealTypesEmulator::Vector3D rlTireLoc;
		UnrealTypesEmulator::Vector3D rrTireLoc;
		UnrealTypesEmulator::Vector3D flTireLoc;
		UnrealTypesEmulator::Vector3D bodyLoc;

		UnrealTypesEmulator::Rotator3D flTireRot;
		UnrealTypesEmulator::Rotator3D frTireRot;
		UnrealTypesEmulator::Rotator3D rlTireRot;
		UnrealTypesEmulator::Rotator3D rrTireRot;
		UnrealTypesEmulator::Rotator3D bodyRot;
	};



	struct TrafficCarSpawnPacket
	{
		int ID;
		uint8_t carType;
	};

	struct TrafficCarDataPacket //A Packet containing data representation of Traffic Car
	{
		int ID;
		UnrealTypesEmulator::Vector3D carLcoation;
		UnrealTypesEmulator::Rotator3D carRotation;
		float carSpeed;
		float zRotationFronLeftWheel;
		float zRotationFronRightWheel;

	};



	// Mo Cap Data
	struct MoCapBonePacket {
		int boneID;
		UnrealTypesEmulator::Vector3D position;
		UnrealTypesEmulator::Quaternion rotation;
	};


	struct MocapFrame {
		std::vector<MoCapBonePacket> bones;

		void Serialize(char* packet, int* offset)
		{
			for (const auto& bone : bones)
			{
				NetworkPacketUtils::SerializePacket(bone, packet, offset);
			}
		}

		void Deserialize(char* packet, int* offset)
		{
			for (size_t i = 0; i < bones.size(); i++)
			{
				MoCapBonePacket bone;
				NetworkPacketUtils::DeserializePacket(bone, packet, offset);
				bones.push_back(bone);
			}
		}
	};


	//Client Animation Packets
	struct PedestrianAnimationPacket {
		float velocity;
		bool isInAir;
	};


	//Server Packets
	struct ServerWelcomePacket
	{
		int id;
	};

	struct SpawnNewMember
	{
		uint8_t clientType;
		int id;
	};
}