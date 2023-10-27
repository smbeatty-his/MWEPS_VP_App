#include <vpMotionUFO.h>
#include <MWEPSApp.h>
#include <BulletManager.h>
#include <ITarget.h>
#include <DebugUtil.h>
#include <vpObject.h>
#include <vpFxParticleSystem.h>
#include <ParticleSystemManager.h>
#include <AimManager.h>
#include <AARManager.h>
#include <SoundManager.h>
#include <TargetManager.h>
#include <GunManager.h>
#include <TPManager.h>
#include <OceanManager.h>
#include <FactoryManager.h>
#include <vpFxSplash.h>
#include <ScenarioParser.h>


///////////////////////////////////////////////////////////////////////////////
///
///	MWEPSApp::~MWEPSApp 
///	
///	@brief Destructor
///
///////////////////////////////////////////////////////////////////////////////

MWEPSApp::~MWEPSApp() 
{
	
}

int MWEPSApp::unconfigure(void)
{
	//SoundManager::Shutdown();
	//BulletManager::Shutdown();
	//ParticleSystemManager::Shutdown();
	//AimManager::Shutdown();
	//TargetManager::Shutdown();
	//GunManager::Shutdown();
	AARManager::Shutdown();
	FactoryManager::Shutdown();
	TPManager::Shutdown();

	return vpApp::unconfigure();
}

/**
 * Configure my app
 */
int MWEPSApp::configure() 
{
    // pre-configuration 

    // configure vega prime system first
    vpApp::configure();

    // post-configuration

    // Increase the reference count by one for all member variables which
    // cache the Vega Prime class instances.
    // 
    // All VSG/Vega Prime class instances are referenced counted. 
    // The initial reference count is 0 after the instance is created. 
    // When the reference count is smaller or equal to 0 in unref(), 
    // the instance will be deleted automatically. Increasing reference
    // count here for all member variables will guarantee that they will
    // not be deleted until myApp is deleted.

    // add a subscriber to the left mouse button so we know when it's been
    // pressed.  Note here that the motion model doesn't create the
    // default mouse input device until the first update so we'll need to
    // specify our own input device for it to use instead.  Note that
    // specifying a channel for the mouse here allows the input to be
    // relative to the channel so the picking will work even if the
    // channel isn't covering the entire window.
    m_pkMotion = *vpMotionUFO::begin();
    vpInputMouse* pkMouse = new vpInputMouse();
	pkMouse->ref();

    pkMouse->setWindow(*vpWindow::begin());
    pkMouse->setChannel(*vpChannel::begin());
    m_pkMotion->setInput(pkMouse);

	AimManager::GetInstance()->SetMouse(pkMouse);
	
	ScenarioParser kParser = ScenarioParser(this);
	kParser.ParseFile(GetScenarioName());

	GunManager::GetInstance()->SetFireType(GunManager::SINGLE_SHOT);
	GunManager::GetInstance()->Configure();
	

    vpInputSourceBoolean* pkLeftMouseButton = pkMouse->getSourceBoolean(vpInputMouse::SOURCE_BOOLEAN_BUTTON_LEFT);
    pkLeftMouseButton->addSubscriber(vpInputSourceBoolean::EVENT_VALUE_CHANGED, this);

    return vsgu::SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
///
///	MWEPSApp::onKeyInput 
///	
///	@brief Handles any key input overrides, passes any input that is not
///		   overridden to vega prime base app
///
///	@param kEvent Mouse event
///	@param pkSource pointer to boolean source result of left mouse button
///					state change
///
///////////////////////////////////////////////////////////////////////////////
void MWEPSApp::onKeyInput(vrWindow::Key kKey, int iMod)
{

	switch(kKey)
	{
#ifdef NO_SHARE_TEST
		case vrWindow::KEY_R:
		case vrWindow::KEY_r:
		{
			printf("Reseting Scenario\n");
			WMEvent kEvent;
			kEvent.bEvent = true;
			kEvent.iEventType = IOS_RESET_SCENARIO;
			TPManager::GetInstance()->TestIncomingEvent(kEvent);
			break;
		}

		case vrWindow::KEY_G:
		case vrWindow::KEY_g:
		{
			printf("Starting Scenario\n");
			WMEvent kEvent;
			kEvent.bEvent = true;
			kEvent.iEventType = IOS_START_SCENARIO;
			TPManager::GetInstance()->TestIncomingEvent(kEvent);
			break;
		}

		case vrWindow::KEY_P:
		case vrWindow::KEY_p:
		{
			m_bMouseMoveActive = ! m_bMouseMoveActive;

			if (m_bMouseMoveActive)
			{
				m_pkMotion->setSpeed(10.0);
				m_pkMotion->setRateHeading(5.0);
				m_pkMotion->setRatePitch(5.0);
			}

			else
			{
				m_pkMotion->setSpeed(0.0);
				m_pkMotion->setRateHeading(0.0);
				m_pkMotion->setRatePitch(0.0);
			}

			break;
		}
		
		case vrWindow::KEY_O:
		case vrWindow::KEY_o:
		{
			printf("Toggle Ocean Enabled\n");
			WMEvent kEvent;
			kEvent.bEvent = true;
			kEvent.iEventType = IOS_SET_ENABLE_OCEAN;
			kEvent.iData[0] = ! m_bEnableOcean;
			TPManager::GetInstance()->TestIncomingEvent(kEvent);
			break;
		}
#endif
		default:
		{
			vpApp::onKeyInput(kKey, iMod);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///
///	MWEPSApp::notify 
///	
///	@brief Listens for changes to state of left mouse button and processes 
///		   appropriate action based on if button is pressed or released
///
///	@param kEvent Mouse event
///	@param pkSource pointer to boolean source result of left mouse button
///					state change
///
///////////////////////////////////////////////////////////////////////////////
void MWEPSApp::notify(vpInputSourceBoolean::Event kEvent, vpInputSourceBoolean* pkSource)
{
	HandleTriggerChange(pkSource->getValue());
}

///////////////////////////////////////////////////////////////////////////////
///
///	MWEPSApp::HandleTriggerChange 
///	
///	@brief Handles changes to state change of gun trigger
///
///	@param bTriggerPull bool value representing whether trigger was pulled or
///		                released
///
///////////////////////////////////////////////////////////////////////////////
void MWEPSApp::HandleTriggerChange(bool bTriggerPull)
{
	if (! AARManager::GetInstance()->IsReviewActive() && m_kState == MWEPSApp::RUNNING)
	{
		if (bTriggerPull)
		{
			GunManager::GetInstance()->Fire();
		}
		else
		{
			GunManager::GetInstance()->TriggerReleased();
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
///
///	MWEPSApp::endFrame 
///	
///	@brief Handles updates for all Manager classes
///
///	@return int 
///
///////////////////////////////////////////////////////////////////////////////
int MWEPSApp::endFrame() const
{
	switch (m_kState)
	{  // States are: UNSET, LOADING, RESET, RUNNING, PAUSED, STOPPED, INVALID
	case MWEPSApp::UNSET:
	{
		//SMB 11 Sep 2023: Show the target before the simulation starts so the
		//                 Operator can start tracking it
		TargetManager::GetInstance()->ShowTarget();
		TargetManager::GetInstance()->Update(m_dElapsedTime, m_dElapsedTime);

		break;
	}
	case MWEPSApp::RUNNING:
		{
			double dDeltaTime = vpKernel::instance()->getSimulationDeltaTime();

			//printf("Delta Sim time: %f\n", dDeltaTime);

			m_dElapsedTime += dDeltaTime;

			//if were are not in After Action Review, update all managers
			if (! AARManager::GetInstance()->IsReviewActive())
			{
				TargetManager::GetInstance()->Update(m_dElapsedTime, dDeltaTime);

				ParticleSystemManager::GetInstance()->Update();

				BulletManager::GetInstance()->Update(dDeltaTime);

				GunManager::GetInstance()->Update(dDeltaTime);

				SoundManager::GetInstance()->Update();

				AimManager::GetInstance()->Update(dDeltaTime);  //SMB: this does nothing - used to move Aim to mouse position
			}

			//else After Action Review will handle updates
			else
			{
				AARManager::GetInstance()->Update();
			}

			if (m_dElapsedTime > m_dScenarioEndTime)
			{
				m_kState = MWEPSApp::STOPPED;
				OceanManager::GetInstance()->DisableOcean();
				//SMB 15 Aug 2023: Notify WeaponManager that Scenario has ended
				TPManager::GetInstance()->PushEvent(IG_EVENT_READY);

#ifdef NO_SHARE_TEST
				WMEvent kEvent;
				strcpy(kEvent.sData, "test.log");
				kEvent.bEvent = true;
				kEvent.iEventType = IOS_WRITE_BINARY_DATA;
				TPManager::GetInstance()->TestIncomingEvent(kEvent);
#endif
			}

			break;
		}
		
		case MWEPSApp::RESET:
		{
			TargetManager::GetInstance()->Reset();
			ParticleSystemManager::GetInstance()->Reset();
			BulletManager::GetInstance()->Reset();
			SoundManager::GetInstance()->Reset();
			AimManager::GetInstance()->Reset();
			GunManager::GetInstance()->Reset();

			OceanManager::GetInstance()->DisableOcean();

			m_kState = MWEPSApp::STOPPED;

			break;
		}
	}

	TPManager::GetInstance()->Update(m_dElapsedTime);

	return vpApp::endFrame();
}

void MWEPSApp::StartScenario(void)
{
	m_dElapsedTime = 0.0;

	m_kState = MWEPSApp::RUNNING;

	TargetManager::GetInstance()->Start();

	if (m_bEnableOcean)
	{
		OceanManager::GetInstance()->EnableOcean();
	}
}

void MWEPSApp::ResetScenario(void)
{
	m_dElapsedTime = 0.0;

	m_kState = MWEPSApp::RESET;
}

void MWEPSApp::PauseScenario(void)
{
	ASSERT(m_kState == MWEPSApp::RUNNING)
	m_kState = MWEPSApp::PAUSED;
	OceanManager::GetInstance()->DisableOcean();
}

void MWEPSApp::ResumeScenario(void)
{
	ASSERT(m_kState == MWEPSApp::PAUSED)
	m_kState = MWEPSApp::RUNNING;

	if (m_bEnableOcean)
	{
		OceanManager::GetInstance()->EnableOcean();
	}
}

void MWEPSApp::EndScenario(void)
{
	m_kState = MWEPSApp::STOPPED;
	OceanManager::GetInstance()->DisableOcean();
#ifdef NO_SHARE_TEST
	
	WMEvent kEvent;
	strcpy(kEvent.sData, "test.log");

	TPManager::GetInstance()->TestIncomingEvent(kEvent);

#endif
}

void MWEPSApp::SetEnableOcean(const bool bEnabled)
{
	m_bEnableOcean = bEnabled;

	if (m_bEnableOcean && m_kState == MWEPSApp::RUNNING)
	{
		OceanManager::GetInstance()->EnableOcean();
	}

	else if(! m_bEnableOcean)
	{
		OceanManager::GetInstance()->DisableOcean();
	}
}