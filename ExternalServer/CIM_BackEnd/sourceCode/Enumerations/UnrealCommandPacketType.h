#pragma once

namespace CIM_Backend
{
	enum class ECommandType : uint8_t
	{
		WorldConfiguration,
		ClientConfiguration,
		ClientWindowConfiguration,
		StartClient,
		UpdateClientData,
		StopClient,
		ShutdownClient
	};
}