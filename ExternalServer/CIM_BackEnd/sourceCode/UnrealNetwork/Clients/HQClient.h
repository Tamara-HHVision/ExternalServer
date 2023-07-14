#pragma once
#include "UnrealClientBase.h"

namespace CIM_Backend
{
	class HQClient : public UnrealClientBase
	{
	public:
		HQClient(HQClientConfiguration* _configuration);

		inline HQClientConfiguration& GetConfiguration() const { return static_cast<HQClientConfiguration&>(*m_configuration); }
	};
}