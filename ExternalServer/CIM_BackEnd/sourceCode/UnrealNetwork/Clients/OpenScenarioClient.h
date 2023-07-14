#pragma once
#include "UnrealClientBase.h"

namespace CIM_Backend
{
	class OpenScenarioClient : public UnrealClientBase
	{
	public:

		OpenScenarioClient(OpenScenarioConfiguration* _configuration);

		inline OpenScenarioConfiguration& GetConfiguration() const { return static_cast<OpenScenarioConfiguration&>(*m_configuration); }
	};
}

