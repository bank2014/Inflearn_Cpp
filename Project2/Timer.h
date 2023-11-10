#pragma once

using namespace std::chrono;
using hrc = high_resolution_clock;

class Timer
{
private:
	duration<float> m_TotalTimeElapsed;
	duration<float> TimeElapsed;
	duration<float, std::milli> m_FrameTime;
	hrc::time_point m_BeforeTime;
	hrc::time_point CurrentTime;
	uint32 FrameCount;
	uint32 m_FPS;

public:
	Timer();
	void UpdateClock();
	void DrawTimeInfo();

	inline float DeltaTime()
	{
		return duration_cast<duration<float>>(m_FrameTime).count();
	}

	inline float TotalTime()
	{
		return m_TotalTimeElapsed.count();
	}
};

