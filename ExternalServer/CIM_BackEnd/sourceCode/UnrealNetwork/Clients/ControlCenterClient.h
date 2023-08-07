#pragma once
#include "cim_pch.h"
#include "UnrealClientBase.h"

namespace CIM_Backend
{
	class ControlCenterClient : public UnrealClientBase
	{
	public:

		ControlCenterClient(ControlCenterConfiguration* _configuration);
		inline ControlCenterConfiguration& GetConfiguration() const { return static_cast<ControlCenterConfiguration&>(*m_configuration); }
	};

}

