#ifndef TRACKER_PIPE_MANAGER_MODULE_H
#define TRACKER_PIPE_MANAGER_MODULE_H

#include <DebugUtil.h>

typedef void* HANDLE;

// paramaters for setting up shared memory
// events from WM
#define	WM_WRITE_SHARE_INDEX		0x00000		// start of first 256kb block
// events from IG
#define WM_READ_SHARE_INDEX			0x40000		// start of second 256kb block
// range scenario configuration data from WM
#define WM_SCENARIO_SHARE_INDEX		0x80000		// start of scenario configuration data

#define WM_READ_SHARE_SIZE			0x40000		// 256kb block read share
#define WM_WRITE_SHARE_SIZE			0x40000		// 256kb block write share
#define WM_SCENARIO_SHARE_SIZE		0x80000		// 512kb block
#define	WM_TOTAL_SHARE_SIZE			0x100000	// 1MByte

// Event types from IOS / WM
#define IOS_EVENT_NONE				0x00
#define IOS_EVENT_READY				0x01

#define	IOS_INITIALIZE_SCENARIO		0x200
#define IOS_START_SCENARIO			0x201
#define IOS_RESET_SCENARIO			0x202
#define	IOS_PAUSE_SCENARIO			0x203
#define IOS_RESUME_SCENARIO			0x204
#define IOS_END_SCENARIO			0x205
#define IOS_NEXT_TARGET_GROUP		0x206
#define IOS_SET_ENVIRONMENT			0x20D
#define IOS_SET_WIND				0x20E
#define IOS_SET_CAMERA_POSITION		0x20F
#define IOS_SET_WEATHER				0x210
#define IOS_NEXT_IG_STATISTICS		0x212
#define IOS_RANDOMIZE_GROUPS		0x213
#define IOS_MARK_HITS_DISKS			0x214
#define IOS_REFRESH_DISKS			0x215
#define IOS_SET_MIN_DELAYSEC		0x216
#define IOS_SET_MAX_DELAYSEC		0x217
#define IOS_SET_HITS_TO_KILL		0x218
#define IOS_WRITE_BINARY_DATA		0x219		// added to trigger write when all lanes are complete for now TBD
#define IOS_EXIT_IGAPP				0x220
#define IOS_SET_TIME				0x22A
#define IOS_SET_COMPASS				0x22B
#define IOS_SET_HUD					0x22C
#define IOS_SET_CAMERA_NAME			0x22D		// added to set by name normal use vs position AAR use
#define IOS_SET_BORDERS				0x22E
#define IOS_ADD_EFFECT_TYPE			0x22F
#define IOS_ADD_TERRAIN_MATERIAL	0x230
#define IOS_SET_REFERENCE_POSITION	0x231
#define IOS_SET_SEA_STATE			0x232
#define IOS_SET_WAVE_DIRECTION		0x233
#define IOS_SET_PEAK_THRESHOLD		0x234
#define IOS_SET_SURFACE_WIND_SPEED	0x235
#define IOS_SET_ENABLE_OCEAN		0x236

#define IOS_LOAD_AAR_DATA			0x100
#define IOS_INITIALIZE_AAR			0x101
#define IOS_START_AAR				0x102
#define IOS_STOP_AAR				0x103
#define IOS_SHOW_BALLISTIC_PATHS	0x104
#define IOS_CLEAR_BALLISTIC_PATHS	0x105
#define IOS_SET_TIME_AAR			0x106
#define IOS_STEP_FWD				0x107
#define IOS_STEP_REV				0x108
#define IOS_RESET_AAR				0x109

// added to size text
#define IG_TEXT_SMALL				18
#define IG_TEXT_MEDIUM				24
#define IG_TEXT_LARGE				32
#define IOS_DISPLAY_TEXT			0x10A

// weapon specific events
#define IOS_WM_AIM					0x300		// aim event
#define	IOS_WM_SHOT					0x301		// path event
#define IOS_WM_LASE					0x302		// lase event
#define IOS_WM_WEAPON_SOUND			0x303		// play Weapon Sound event at IG via FMod
#define IOS_WM_CROSSHAIR			0x304		// crosshair positioning
#define IOS_WM_SHOW_CROSSHAIR		0x305		// show/hide crosshair
#define IOS_WM_SHOW_CURSOR			0x306		// motion model cursor enable disable

#define IOS_VIEW_FOV_SYMMETRIC		0x400		//symmetric field of view change
#define IOS_VIEW_FOV_ASYMMETRIC		0x401		//asymmetric field of view change
#define IOS_VIEW_FOV_SCALE			0x402		//field of view scale change
#define IOS_VIEW_FOV_SYMMETRIC_DIAGONAL	0x403	//diagonal symmetric field of view change
#define IOS_VIEW_OBSERVER_POSITION	0x404		//observer position change 

// Event types from IG to IOS/WM
#define IG_EVENT_NONE				0x00
#define IG_EVENT_READY				0x01
#define IG_SCENARIO_COMPLETE		0x300
#define IG_CAMERA_POSITION			0x301		// camera position set to IG, status from IG
#define IG_LASE_RETURN				0x302       // lase range results
#define IG_MOUSE_FIRE				0x303		// fire single shot at x,y pixel location

// Event data sizes, currently definitions shared by both structs
#define	NUM_EVENTS					16			// weapon/ig event circular buffer count
#define	NUM_POINTS					300			// path points per ballistic 
#define NUM_INTS					8			// int array data size
#define NUM_FLOATS					8			// float array data size
#define	NUM_CHARS					512			// char buffer size
#define MAX_STRING_LEN				1024

#define WM_EVENT_SIZE				4696		// size of WM write event struct
#define IG_EVENT_SIZE				72			// size of IG write event struct

// THE GOAL OF THIS WAS TO SHARE THIS FILE ACROSS .NET and Delta3D projects
// KEEP THESE FILES UP TO DATE ON BOTH SIDES
// defined in scenario configurationbase.h
#define MAX_TARGET_MODELS			64
#define	MAX_GROUPS					64
#define	MAX_GROUP_TARGETS			64
#define MAX_NAME_LEN				64

#define TARGET_MODELS_INDEX			144
#define TARGET_GROUPS_INDEX			33680
#define GROUP_DATA_SIZE				5768
#define GROUP_TARGET_SIZE			88		// size of IG write event struct

typedef struct pathPnt
{
	float	x;
	float	y;
	float	z;
} PathPoints;									// size 12 bytes

typedef struct WMEvnt
{
	int			bEvent;						// 4, event pending flag
	int			iEventType;					// 4
	int			iData[NUM_INTS];			// 32, integer event data
	float		fData[NUM_FLOATS];			// 32, float event data 72
	char		sData[MAX_STRING_LEN];
	PathPoints	balPath[NUM_POINTS];		// max points 300 * 12, 3600 + 72
} WMEvent;

typedef struct IGEvnt
{
	int			bEvent;						// 4
	int			iEventType;					// 4
	int			iData[NUM_INTS];			// 32
	float		fData[NUM_FLOATS];			// 32
} IGEvent;									// 72 per

typedef struct vpIGShare
{
	IGEvent		Ev[NUM_EVENTS];				// 72 * 16
} VegaPrimeIGShare;

typedef	struct weaponManagerShare
{
	WMEvent		Ev[NUM_EVENTS];				// 4696 * 16
} WeaponManagerShare;

class MWEPSApp;

class TPManager
{

public:

	static inline void Initialize(const char* sShareNameWeaponManager)
	{
		ASSERT(sShareNameWeaponManager)
		ASSERT(! s_pkInstance)
		s_pkInstance = new TPManager(sShareNameWeaponManager);
	}

	static inline TPManager* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		ASSERT(s_pkInstance)
		delete s_pkInstance;
	}

	void Update(const double dElapsedTime);
	void ClearShares(const char* sText);
    const int FindEventSlot(void) const;
	const bool PushEvent(const int iEventType);
	const bool PushEvent(const int iEventType, const int aiData[]);
	const bool PushEvent(const int iEventType, const float afData[]);
	const bool PushEvent(const int iEventType, const int aiData[], const float afData[]);
	const char* GetIGShareName(void) const;
	const int ProcessIncomingEvents(const double dElapsedTime);
	const bool ProcessInitialization(MWEPSApp* pkApp);

	void TestIncomingEvent(WMEvent& kEvent);

private:
	TPManager(const char* sShareNameWeaponManager);
	~TPManager(void);
	static TPManager*	s_pkInstance;
	WeaponManagerShare* m_pkWMShare;		// event data from WM
	VegaPrimeIGShare*	m_pkIGShare;		// event data from IG
	MWEPSApp*			m_pkApp;
	HANDLE				m_hWMShare;
	char				m_sIGShareName[MAX_NAME_LEN];
};

#endif