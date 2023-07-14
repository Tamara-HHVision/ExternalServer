#pragma once
#include "UnrealClientBase.h"

namespace CIM_Backend
{
	/// <summary>
	/// Class represents observer mocap client
	/// </summary>
	class MotionCaptureClient : public UnrealClientBase
	{
	public:

		MotionCaptureClient(MocapConfiguration* _configuration);
		inline MocapConfiguration& GetConfiguration() const { return static_cast<MocapConfiguration&>(*m_configuration); }
	};
}