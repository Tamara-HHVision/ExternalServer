#pragma once
#include <iostream>
#include <chrono>

namespace CIM_Backend
{
	class Timer
	{
		std::chrono::time_point<std::chrono::steady_clock> m_end;
		std::chrono::time_point<std::chrono::steady_clock> m_start;
		std::chrono::duration<float> m_duration;

	public:
		Timer()
		{
			m_start = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			m_end = std::chrono::high_resolution_clock::now();
			m_duration = m_end - m_start;

			float ms = m_duration.count() * 1000.f;

			Log::LogInfoToFile("Timer took {}", ms);
		}
	};

}

