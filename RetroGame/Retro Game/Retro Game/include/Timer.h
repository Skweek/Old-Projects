////////////////////////////////////////////////////////////
// File: Timer.h
// Author: Nick Smith
// Date Created: 6th May 2013
// Brief: Simple Timer
////////////////////////////////////////////////////////////

#ifndef _TIMER_H_
#define _TIMER_H_

struct Timer
{
	float m_fEndTime;
	float m_fCurrentTime;
	float m_fInterval;

	bool m_bTimerFinished;

	// Start the timer and set the end time
	void Start( float a_fEndTime )
	{
		m_bTimerFinished = false;
		m_fCurrentTime = 0.f;
		m_fEndTime = a_fEndTime;
		m_fInterval = 0.01f;
	}

	// Resets the timer time to 0, keeps the end time
	void Reset()
	{
		m_fCurrentTime = 0.f;
		m_bTimerFinished = false;
	}

	// Updates the timer time and determines if timer is finished
	void Update()
	{
		m_fCurrentTime += m_fInterval;

		if ( m_fCurrentTime >= m_fEndTime )
		{
			m_bTimerFinished = true;
		}
	}
};

#endif // _TIMER_H_