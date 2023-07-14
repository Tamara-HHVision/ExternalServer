#pragma once
#include "UnrealClientBase.h"


namespace CIM_Backend
{
	/// <summary>
	/// Client represents the main vehicle
	/// </summary>
	class EgoVehicleClient : public UnrealClientBase
	{
	public:

		EgoVehicleClient(EgoVehicleConfiguration* _configuration);

		inline EgoVehicleConfiguration& GetConfiguration() const { return static_cast<EgoVehicleConfiguration&>(*m_configuration); }
	};
}
