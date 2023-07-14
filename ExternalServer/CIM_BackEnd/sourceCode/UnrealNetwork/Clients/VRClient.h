#pragma once
#include "UnrealClientBase.h"

namespace CIM_Backend
{
    /// <summary>
    /// Class represents the VR Unreal Pawn
    /// </summary>
    class VRClient : public UnrealClientBase
    {
    public:
        VRClient(VRConfiguration* _configuration);
        inline VRConfiguration& GetConfiguration() const { return static_cast<VRConfiguration&>(*m_configuration); }
    };
}

