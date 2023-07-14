#pragma once
#include "UnrealClientBase.h"

namespace CIM_Backend
{
	/// <summary>
	/// Class represents observer Unreal client
	/// </summary>
	class ObserverClient : public UnrealClientBase
	{
	public:
		ObserverClient(ObserverConfiguration* _configuration);
		inline ObserverConfiguration& GetConfiguration() const { return static_cast<ObserverConfiguration&>(*m_configuration); }
	};
}