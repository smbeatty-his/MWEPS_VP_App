#ifndef MWEPS_APP_MODULE_H
#define MWEPS_APP_MODULE_H

#include <vpApp.h>
#include <vpInputMouse.h>
#include <DebugUtil.h>

class vpObserver;
class vpFxParticleSystem;
class vpMotionUFO;

///////////////////////////////////////////////////////////////////////////////
///
/// @class MWEPSApp
///
///	@brief This class is the derived app that serves as the main access point
///		   to the Vega Prime engine.
///
///////////////////////////////////////////////////////////////////////////////

// we need to derive our application class from the vpInputSourceBoolean
// subscriber class so we can be notified of mouse button presses
class MWEPSApp : public vpApp, public vpInputSourceBoolean::Subscriber
{

public:

	enum ScenarioState
	{
		UNSET,
		LOADING,
		RESET,
		RUNNING,
		PAUSED,
		STOPPED,
		INVALID
	};

    /**
     * Constructor
     */
    MWEPSApp(){}

    /**
     * Destructor
     */
    ~MWEPSApp(); 
    
    /**
     * Configure my app
     */
    int configure(); 

    /**
     * Override keyboard input
     */
    virtual void onKeyInput(vrWindow::Key kKey, int iMod);

	const inline void SetInitializationFiles(const char* sFileNames)
	{
		ASSERT(sFileNames)
		strncpy(m_sACFName, sFileNames, 256);
		strncpy(m_sScenarioName, &(sFileNames[512]), 256);
//		strncpy(m_sScenarioName, &(sFileNames[256]), 256);
	}

	const inline void SetEndTime(const double dEndTime) { m_dScenarioEndTime = dEndTime; }

	const inline char* GetACFName(void) { return m_sACFName; }
	const inline char* GetScenarioName(void) { return m_sScenarioName; }
	const inline double GetElapsedTime(void) const { return m_dElapsedTime; }
	
	void SetEnableOcean(const bool bEnabled);

    /**
     * notification of changes to left button mouse input
     */
    virtual void notify(vpInputSourceBoolean::Event kEvent, vpInputSourceBoolean *pkSource);

	virtual int unconfigure(void);

	void HandleTriggerChange(bool bTriggerPull);

	void ResetScenario(void);
	void StartScenario(void);
	void PauseScenario(void);
	void ResumeScenario(void);
	void EndScenario(void);

private:
	
	bool m_bMouseMoveActive = false; //SMB: initialized to avoid warning C26495
	mutable bool m_bEnableOcean = false; //SMB: initialized to avoid warning C26495
	virtual int endFrame() const;
	mutable ScenarioState m_kState = UNSET; //SMB: initialized to avoid warning C26495
	vpMotionUFO* m_pkMotion;
	mutable double m_dElapsedTime = 0.0; //SMB: initialized to avoid warning C26495
	double m_dScenarioEndTime = 0.0; //SMB: initialized to avoid warning C26495
	char m_sACFName[256] = { 0 }; //SMB: initialized to avoid warning C26495
	char m_sScenarioName[256] = { 0 }; //SMB: initialized to avoid warning C26495
};

#endif
