#pragma once

namespace CIM_Backend::UnrealTypesEmulator
{
	struct Vector3D
	{
		float x;
		float y;
		float z;
	};

	struct Rotator3D
	{
		float pitch;
		float yaw;
		float roll;
	};

	struct Quaternion
	{
		float x;
		float y;
		float z;
		float w;
	};
}