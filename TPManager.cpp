#include <TPManager.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <MWEPSApp.h>
#include <AimManager.h>
#include <BulletManager.h>
#include <WeatherManager.h>
#include <OceanManager.h>
#include <SoundManager.h>
#include <ViewManager.h>
#include <PerformanceLogger.h>
#include <TargetManager.h>

#define SLOT_NOT_FOUND -1

TPManager* TPManager::s_pkInstance = NULL;

TPManager::TPManager(const char* sShareNameWeaponManager) : m_hWMShare(NULL), m_pkWMShare(NULL), m_pkIGShare(NULL),
															m_pkApp(NULL)
{
	ASSERT(sShareNameWeaponManager)
	// SMB 27 Jul 2023 WAS: m_hWMShare = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0,
	// Invalid File Handle creates map in page file
	m_hWMShare = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,
										WM_TOTAL_SHARE_SIZE, sShareNameWeaponManager);

	sprintf(m_sIGShareName, "%s", sShareNameWeaponManager);

	if ( !m_hWMShare )
	{
		//DWORD dw = GetLastError();
		//sprintf(message, "CreateFileMapping failed: GetLastError returned %u\n", dw); 

		LPVOID lpMsgBuf;
		if (!FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR)&lpMsgBuf,
			0,
			NULL))
		{
			// Handle the error.
		}
		// Process any inserts in lpMsgBuf.
		// Display the string.
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION);
		// Free the buffer.
		LocalFree(lpMsgBuf);

		printf("Problem creating WM Shared Memory Map %p.\r\n", m_hWMShare);
		assert(0);
	}
	else 
	{
	//	Sleep(5000); // SMB: wait 30 seconds to attach debugger
		printf("WM Shared Memory Map created %d named %s.\r\n", (int) m_hWMShare, sShareNameWeaponManager);
	}

	m_pkWMShare = (WeaponManagerShare *) MapViewOfFile
							(m_hWMShare, FILE_MAP_READ | FILE_MAP_WRITE, 0, WM_WRITE_SHARE_INDEX, WM_WRITE_SHARE_SIZE);

	ASSERT(m_pkWMShare)

	m_pkIGShare = (VegaPrimeIGShare *) MapViewOfFile
							(m_hWMShare, FILE_MAP_READ | FILE_MAP_WRITE, 0, WM_READ_SHARE_INDEX, WM_READ_SHARE_SIZE);

	ASSERT(m_pkIGShare)

	//SMB: 19 Oct 2023 - handle initialization when we get the IOS_INITIALIZE_SCENARIO command
		// WAS 
	//m_pkWMShare->Ev[0].iEventType = IOS_INITIALIZE_SCENARIO;
	//m_pkWMShare->Ev[0].bEvent = true;
	//	strcpy(m_pkWMShare->Ev[0].sData, "Track3mRadiusBlueSphere.acf");
	//	strcpy(&(m_pkWMShare->Ev[0].sData[256]), "Track1000mBlueSphere30sec.xml");	
	//  printf("m_pkWMShare: ACF Filename: %s     Scenario Filename: %s \r\n",
	//m_pkWMShare->Ev[0].sData, &(m_pkWMShare->Ev[0].sData[512]));

	//SMB: 19 Oct 2023 - Need to push this event to get WeaponManager to send IOS_INITIALIZE_SCENARIO command
	PushEvent(IG_EVENT_READY);

	// End of handle initialization

}

TPManager::~TPManager(void)
{
	UnmapViewOfFile(m_hWMShare);
	UnmapViewOfFile(m_pkIGShare);
	CloseHandle(m_hWMShare);
}

void TPManager::Update(const double dElapsedTime)
{
	ProcessIncomingEvents(dElapsedTime);
}

void TPManager::ClearShares(const char* sText)
{
	memset(m_pkWMShare, 0, sizeof(WeaponManagerShare));
	memset(m_pkIGShare, 0, sizeof(VegaPrimeIGShare));
}

// push event into first available event buffer
// returns true if event pushed false if no event buffers are available (app exception)
const bool TPManager::PushEvent(const int iEventType)
{ 	
	int iEv = FindEventSlot();

	if (iEv != SLOT_NOT_FOUND)	// if slot found push event
	{
		m_pkIGShare->Ev[iEv].iEventType = iEventType;	// push event type
		m_pkIGShare->Ev[iEv].bEvent = true;	// set event pending
	}

	return (iEv != SLOT_NOT_FOUND);
}

// push event into first available event buffer
// returns true if event pushed false if no event buffers are available (app exception)
const bool TPManager::PushEvent(const int iEventType, const int aiData[]) // event type with int event data
{ 
	int iEv = FindEventSlot();
	if (iEv != SLOT_NOT_FOUND)	// if slot found push event
	{
		m_pkIGShare->Ev[iEv].iEventType = iEventType;

		// push event type
		if (aiData) 
		{
			memcpy(m_pkIGShare->Ev[iEv].iData, aiData, sizeof(int) * NUM_INTS);	// push int data
		}
		m_pkIGShare->Ev[iEv].bEvent = true;		// set event pending
	}
	return (iEv != SLOT_NOT_FOUND);
}

// push event into first available event buffer
// returns true if event pushed false if no event buffers are available (app exception)
const bool TPManager::PushEvent(const int iEventType, const float afData[])	// event type with float event data
{ 
	int iEv = FindEventSlot();
	if (iEv != SLOT_NOT_FOUND)	// if slot found push event
	{
		m_pkIGShare->Ev[iEv].iEventType = iEventType; // push event type
		
		if (afData)
		{
			memcpy(m_pkIGShare->Ev[iEv].fData, afData, sizeof(float) * NUM_FLOATS);	// push float data
		}

		m_pkIGShare->Ev[iEv].bEvent = true;	// set event pending
	}

	return (iEv != SLOT_NOT_FOUND);
}

// returns true if event pushed false if no event buffers are available (app exception)
const bool TPManager::PushEvent(const int iEventType, const int aiData[], const float afData[])
{ 
	int iEv = FindEventSlot();

	if (iEv != SLOT_NOT_FOUND)	// if slot found push event
	{
		m_pkIGShare->Ev[iEv].iEventType = iEventType;	// push event type
		if (aiData) 
		{
			memcpy(m_pkIGShare->Ev[iEv].iData, aiData, sizeof(int) * NUM_INTS);		// push int data
		}

		if (afData)
		{
			memcpy(m_pkIGShare->Ev[iEv].fData, afData, sizeof(float) * NUM_FLOATS);	// push float data
		}

		m_pkIGShare->Ev[iEv].bEvent = true;				// set event pending
	}

	return (iEv != SLOT_NOT_FOUND);
}

// search WM share for first available event slot
const int TPManager::FindEventSlot(void) const
{
	int	iSlotAvailable = SLOT_NOT_FOUND;	// initialize index as not found
	
	for ( int i = 0; i < NUM_EVENTS; i++ )
	{
		if ( m_pkIGShare->Ev[i].bEvent == false )
		{
			iSlotAvailable = i;			// return first available slot index
			break;
		}
	}

	printf("Finding Event Slot: %d\n", iSlotAvailable);

	return iSlotAvailable;
}

const int TPManager::ProcessIncomingEvents(const double dElapsedTime)
{

	int iEventsProcessed = 0;
	// add Event vector for IOS based events AAR TBD, weather, time, etc
	for ( int i = 0; i < NUM_EVENTS; i++ )
	{
		if (m_pkWMShare->Ev[i].bEvent)
		{
			iEventsProcessed++;
			int iEventType = m_pkWMShare->Ev[i].iEventType;

			switch (iEventType)
			{

#pragma region Scenario Events

				case IOS_RESET_SCENARIO:
				{
					m_pkApp->ResetScenario();
					
					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}
				
				case IOS_START_SCENARIO:
				{
					m_pkApp->StartScenario();

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_PAUSE_SCENARIO:
				{
					m_pkApp->PauseScenario();

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_RESUME_SCENARIO:
				{
					m_pkApp->ResumeScenario();

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_END_SCENARIO:
				{
					m_pkApp->EndScenario();

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_WRITE_BINARY_DATA:
				{
					PerformanceLogger::GetInstance()->LogPerformanceData(m_pkWMShare->Ev[i].sData);

					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				//SMB: 26 Oct 2023 Added this case - WeaponManager sends this event, previously unhandled
				case IOS_EXIT_IGAPP:
				{
					m_pkApp->EndScenario();
					m_pkApp->breakFrameLoop(); // This will purportedly end the run loop - still get Error Box popup

					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}
#pragma endregion

#pragma region View Events
				case IOS_VIEW_FOV_SYMMETRIC:
				{
					ViewManager::GetInstance()->ChangeObserverFOVSymmetric(m_pkWMShare->Ev[i].fData[0],
																		   m_pkWMShare->Ev[i].fData[1]);

					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_VIEW_FOV_ASYMMETRIC:
				{
					ViewManager::GetInstance()->ChangeObserverFOVAsymmetric(m_pkWMShare->Ev[i].fData[0],
																			m_pkWMShare->Ev[i].fData[1],
																			m_pkWMShare->Ev[i].fData[2],
																			m_pkWMShare->Ev[i].fData[3]);

					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_VIEW_FOV_SYMMETRIC_DIAGONAL:
				{
					ViewManager::GetInstance()->ChangeObserverFOVScale(m_pkWMShare->Ev[i].fData[0]);

					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_VIEW_FOV_SCALE:
				{
					ViewManager::GetInstance()->ChangeObserverFOVScale((double) m_pkWMShare->Ev[i].fData[0]);

					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				

				case IOS_VIEW_OBSERVER_POSITION:
				{
					ViewManager::GetInstance()->ChangeObserverPosition(vuVec3<double>(m_pkWMShare->Ev[i].fData[0],
																					  m_pkWMShare->Ev[i].fData[1],
																					  m_pkWMShare->Ev[i].fData[2]));

					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

#pragma endregion

#pragma region IG Environmental Settings

				case IOS_SET_WIND:
				{
					vuVec3<float> vfDir = vuVec3<float>(m_pkWMShare->Ev[i].fData[1], m_pkWMShare->Ev[i].fData[2],
														m_pkWMShare->Ev[i].fData[3]);
					WeatherManager::GetInstance()->SetWind(m_pkWMShare->Ev[i].fData[0], vfDir);

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_SET_WEATHER:
				{
					WeatherManager::GetInstance()->SetWeather
									((WeatherManager::WeatherState) m_pkWMShare->Ev[i].iData[0]);

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_SET_TIME:
				{
					WeatherManager::GetInstance()->SetTime(m_pkWMShare->Ev[i].fData[0], m_pkWMShare->Ev[i].iData[0],
														   m_pkWMShare->Ev[i].iData[1], m_pkWMShare->Ev[i].iData[2]);

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}
				
				case IOS_SET_REFERENCE_POSITION:
				{
					WeatherManager::GetInstance()->SetReferencePosition
														(m_pkWMShare->Ev[i].fData[0], m_pkWMShare->Ev[i].fData[1]);

					m_pkWMShare->Ev[i].bEvent = false;
					
					break;
				}
#pragma endregion

#pragma region Ocean Settings
				
				case IOS_SET_SEA_STATE:
				{
					OceanManager::GetInstance()->SetSeaState(m_pkWMShare->Ev[i].iData[0]);

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_SET_WAVE_DIRECTION:
				{
					OceanManager::GetInstance()->SetDominantWaveDirection(m_pkWMShare->Ev[i].fData[0]);

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_SET_PEAK_THRESHOLD:
				{
					OceanManager::GetInstance()->SetPeakThreshold(m_pkWMShare->Ev[i].fData[0]);

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_SET_SURFACE_WIND_SPEED:
				{
					OceanManager::GetInstance()->SetSurfaceWindSpeed(m_pkWMShare->Ev[i].fData[0]);

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

				case IOS_SET_ENABLE_OCEAN:
				{

					m_pkApp->SetEnableOcean(m_pkWMShare->Ev[i].iData[0] != 0);

					m_pkWMShare->Ev[i].bEvent = false;

					break;
				}

#pragma endregion

#pragma region Local / Remote Weapon Interaction Events

				case IOS_WM_WEAPON_SOUND:
				{
					SoundManager::GetInstance()->PlayAmbientSound("Gunshot");
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_WM_SHOT:
				{
					BulletManager::GetInstance()->PushBulletPath(m_pkWMShare->Ev[i], dElapsedTime);
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_WM_AIM:
				{
					AimManager::GetInstance()->PushAim(m_pkWMShare->Ev[i], dElapsedTime);
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}
				// SMB 06Nov2023 - We don't receive this event now that Crosshair responds to Laser spot
				//				   That's handled with PushAim and event IOS_WM_AIM
				/*
				case IOS_WM_CROSSHAIR:
				{
					AimManager::GetInstance()->UpdateCrosshairPosition(m_pkWMShare->Ev[i]);
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}
				*/

				case IOS_WM_LASE:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				//SMB: 26 Oct 2023 - Handle these events also, which are sent from WeaponManager
				case IOS_WM_SHOW_CROSSHAIR:
				{
					// pointer to incomplete class type is not allowed
					//AimManager::GetInstance()->GetCrosshair()->setEnable(true);
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_WM_SHOW_CURSOR:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}


#pragma endregion

#pragma region After Action Review Events

				case IOS_LOAD_AAR_DATA:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_INITIALIZE_AAR:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_START_AAR:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_RESET_AAR:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_STOP_AAR:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_STEP_FWD:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_STEP_REV:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_SHOW_BALLISTIC_PATHS:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_CLEAR_BALLISTIC_PATHS:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

				case IOS_SET_CAMERA_POSITION:
				{
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}

#pragma endregion

				default:
				{
					DEBUG_PRINT("SMB: Unprocessed Event Detected ");
					printf("%i \n", iEventType);
					m_pkWMShare->Ev[i].bEvent = false;
					break;
				}
			}
		}
	}

	return iEventsProcessed;
}

const bool TPManager::ProcessInitialization(MWEPSApp* pkApp)
{
	for ( int i = 0; i < NUM_EVENTS; i++ )
	{
		if (m_pkWMShare->Ev[i].bEvent)
		{
			ASSERT(m_pkWMShare->Ev[i].iEventType == IOS_INITIALIZE_SCENARIO)

			pkApp->SetInitializationFiles(m_pkWMShare->Ev[i].sData);

			printf("Proc Init: ACF Filename: %s     Scenario Filename: %s \r\n",
				pkApp->GetACFName(), pkApp->GetScenarioName());

			printf("Processing initialization with event index %d\n", i);

			m_pkApp = pkApp;

			PushEvent(IG_EVENT_READY);

			m_pkWMShare->Ev[i].bEvent = false;

			return true;
		}
	}

	return false;
}


void TPManager::TestIncomingEvent(WMEvent& kEvent)
{
	int iIndex = 0;

	for (iIndex; iIndex < NUM_EVENTS; ++iIndex)
	{
		if (m_pkWMShare->Ev[iIndex].bEvent == false)
		{
			break;
		}
	}

	if (iIndex < NUM_EVENTS)
	{
		m_pkWMShare->Ev[iIndex].bEvent = true;
		memcpy(&(m_pkWMShare->Ev[iIndex]), &kEvent, sizeof(WMEvent));
	}

	else
	{
		printf("Event fired, no slot found for it\n");
	}
}
