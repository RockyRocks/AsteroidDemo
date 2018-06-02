#ifndef __WINTIMER_H
#define __WINTIMER_H

#include <windows.h>
#include "..\utils\Singleton.h"

#define WIN32_LEAN_AND_MEAN

// WinTimer Description
//
// A windows only timer based on the implementation at NeHe.
class WinTimer : public Singleton<WinTimer>
{
	friend Singleton<WinTimer>;

public:
	WinTimer();
	void Update();
	float Get_dt() const;
	float GetTime() const;
	void Initialize();

	const float getDeltaTime();
	void setDeltaTime(const float dt);

private:
	float m_DeltaTime;

	float dt, td, td2;
	__int64       frequency;									// Timer Frequency
	float         resolution;									// Timer Resolution
	unsigned long mm_timer_start;								// Multimedia Timer Start Value
	unsigned long mm_timer_elapsed;								// Multimedia Timer Elapsed Time
	bool		  performance_timer;							// Using The Performance Timer?
	__int64       performance_timer_start;						// Performance Timer Start Value
	__int64       performance_timer_elapsed;					// Performance Timer Elapsed Time

};

inline const float WinTimer::getDeltaTime()
{
	return m_DeltaTime;
}

inline void WinTimer::setDeltaTime(const float dt)
{
	m_DeltaTime = dt;
}

#endif
