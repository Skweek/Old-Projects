////////////////////////////////////////////////////////////
// File: Startup.h
// Author: Nick Smith
// Date Created: 12th May 2013
// Brief: Startup functions
////////////////////////////////////////////////////////////

#ifndef _STARTUP_H_
#define _STARTUP_H_

#include "Utilities.h"

class DECLDIR Startup
{
public:
	static Startup* Create();
	static Startup* Get();
	static void Delete();

	
	int InitialiseLibraries( int a_iScreenHeight, int a_iScreenWidth );
	void ClearScreen( int a_iWindowID, float a_fR, float a_fG, float a_fB, float a_fA );

	void ReloadEngine();
	bool Update();
	
	inline double GetDeltaTime()
	{
		return m_dDeltaTime;
	}
	inline float GetFPS()
	{
		return m_fFPS;
	}

private:
	Startup();
	~Startup();

	static Startup* m_pInstance;
	void UpdateDeltaTime();

	double m_dDeltaTime;
	double m_dGameTime;
	double m_dFrameTime;
	float m_fFPS;

	bool m_bDebugInfo;

};

#endif // _STARTUP_H_