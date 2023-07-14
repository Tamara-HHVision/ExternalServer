#pragma once
namespace CIM_Backend
{
	enum class EWeatherSettings : uint8_t
	{
        ClearSky,
        PartlyCloudy,
        Cloudy,
        Overcast,
        Foggy,
        LightRain,
        Rain,
        Thunderstorm,
        LightSnow,
        Snow,
        Blizzard
	};
}