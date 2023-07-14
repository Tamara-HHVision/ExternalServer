#include "cim_pch.h"
#include "NetworkPacketUtils.h"

void CIM_Backend::NetworkPacketUtils::WriteVector(char* buf, UnrealTypesEmulator::Vector3D vector, int* writeOffset)
{
	WriteSimpleData(buf, vector.x, writeOffset);
	WriteSimpleData(buf, vector.y, writeOffset);
	WriteSimpleData(buf, vector.z, writeOffset);
}

void CIM_Backend::NetworkPacketUtils::WriteQuaternion(char* buf, UnrealTypesEmulator::Quaternion quat, int* writeOffset)
{
	WriteSimpleData(buf, quat.x, writeOffset);
	WriteSimpleData(buf, quat.y, writeOffset);
	WriteSimpleData(buf, quat.z, writeOffset);
	WriteSimpleData(buf, quat.w, writeOffset);
}

CIM_Backend::UnrealTypesEmulator::Vector3D CIM_Backend::NetworkPacketUtils::ReadVector(char* buf, int* readoffset)
{
	UnrealTypesEmulator::Vector3D vector;
	vector.x = ReadSimpleData<float>(buf, readoffset);
	vector.y = ReadSimpleData<float>(buf, readoffset);
	vector.z = ReadSimpleData<float>(buf, readoffset);

	return vector;
}

CIM_Backend::UnrealTypesEmulator::Quaternion CIM_Backend::NetworkPacketUtils::ReadQuaternion(char* buf, int* readOffset)
{
	UnrealTypesEmulator::Quaternion quat;

	quat.x = ReadSimpleData<float>(buf, readOffset);
	quat.y = ReadSimpleData<float>(buf, readOffset);
	quat.z = ReadSimpleData<float>(buf, readOffset);
	quat.w = ReadSimpleData<float>(buf, readOffset);

	return quat;
}