#include "stdafx.h"
#include "Timer.h"

Timer::Timer() :
	m_TotalTimeElapsed(duration<float>(0)),
	TimeElapsed(duration<float>(0)),
	m_FrameTime(duration<float>(0)),
	FrameCount(0),
	m_FPS(0),
	m_BeforeTime(hrc::now()) {}

void Timer::UpdateClock() {
	CurrentTime = hrc::now();
	m_FrameTime = CurrentTime - m_BeforeTime;
	m_BeforeTime = CurrentTime;

	m_TotalTimeElapsed += m_FrameTime;
	
	TimeElapsed += m_FrameTime;
	if (TimeElapsed.count() >= 1.0) {
        m_FPS = FrameCount;
        FrameCount = 0;

		//TimeElapsed -= TimeElapsed;
		TimeElapsed = duration<float>(0);
    }
	else {
        ++FrameCount;
    }
}

void Timer::DrawTimeInfo() {
	std::cout 
		<< "[TotalTimeElapsed] "<< m_TotalTimeElapsed.count()	<< "s	"
		<< "[Frametime] "		<< m_FrameTime.count()		<< "ms	"
		<< "[Fps] "				<< m_FPS						<< '\n';
}





