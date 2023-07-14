#pragma once
#include "cim_pch.h"
#include "UnrealClientBase.h"

namespace CIM_Backend
{
	/// <summary>
	/// Class represents 3rd person Unreal client
	/// </summary>
	class PedestrianClient : public UnrealClientBase
	{
	public:

		PedestrianClient(PedestrianConfiguration* _configuration);
		inline PedestrianConfiguration& GetConfiguration() const { return static_cast<PedestrianConfiguration&>(*m_configuration); }
	};
}