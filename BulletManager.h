#ifndef BULLET_MANAGER_MODULE_H
#define BULLET_MANAGER_MODULE_H

#include <vuVec3.h>
#include <vuList.h>
#include <vpIsectorLOS.h>
#include <DebugUtil.h>
#include <BulletRecord.h>


#define MAX_NUM_TRACERS				20
#define MAX_TARGET_MODELS			64
#define	MAX_GROUPS					64
#define	MAX_GROUP_TARGETS			64
#define MAX_NAME_LEN				64
#define	NUM_POINTS					300			// path points per ballistic

#define NUM_BULLETS

class vsGeometry;
class vrGeometry;
class vsRenderStrategyFrameGeometry;
class vpFxParticleSystem;
class vsNode;

typedef struct WMEvnt WMEvent;

///////////////////////////////////////////////////////////////////////////////
///
/// @class BulletManager
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

typedef struct shotPath
{
	int				m_iWeaponType;				//weapon type, round type
	int				m_iNumPoints;					//number of path points
    int				m_iPathIndex;
	float			m_fImpactScreenX;
	float			m_fImpactScreenY;			//currently used to index path elements, used by flyout!!!!!!
    double			m_dEventTime;					//shot fired time
	double			m_dTimeInterval;
	double			m_dImpactTime;	
	double			m_dTotalTravelTime;
	vuVec3<double>	m_pnt[NUM_POINTS];
} ShotPath;

class BulletManager
{
public:

	void Update(double dTime);
	void Reset(void);
	void Start(void);
	void Fire(const vuVec3<double>& pvdEntryPoint);
	void Fire(void);
	void SetWindVelocity(const vuVec3<double>& pvdWindVel) { m_vdWindVelocity = pvdWindVel; }
	const vuVec3<double>& GetWindVelocity(void) const { return m_vdWindVelocity; }
	const inline bool& GetDrawTracers(void) const { return m_bDrawTracers; } 
	inline void AddExpiredBullet(BulletRecord* pkRecord) {  m_lpkExpiredBullets.push_back(new BulletRecord(*pkRecord)); }
	void PrintAllChildren(vsNode* pkNode);
	void PrintAllParents(vsNode* pkNode);
	void PushBulletPath(const WMEvent& kEvent, const double dElapsedTimeSec);
	void GenerateBulletPath(WMEvent* pkEvent);
	const inline vuList<BulletRecord*>& GetBulletRecords(void) const { return m_lpkExpiredBullets; }
	void ClearBulletRecords(void);

	static inline BulletManager* GetInstance(void) 
	{ 
		ASSERT(s_pkInstance)
		return s_pkInstance; 
	}

	static void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new BulletManager();
	}

	static void Shutdown(void);

private:

	// a simple structure to store our tracer data
    struct BulletTracer 
	{
		BulletTracer() : m_pkRecord(NULL), m_isector(NULL), m_pkPath(NULL)
		{

		}
		~BulletTracer(void)
		{
			if (m_isector != NULL)
			{
				m_isector->unref();
			}
			
			delete m_pkRecord;
			
		}

		void UpdateVelocity(double dDeltaTime)
		{
			m_vdVelocity = m_pkPath->m_pnt[m_pkPath->m_iPathIndex];

			m_pkPath->m_iPathIndex++;
		}
        // true if the tracer is currently active
        bool m_bActive = false; //SMB: initialized to avoid warning C26495
		bool m_bTest = false; //SMB: initialized to avoid warning C26495
		BulletRecord* m_pkRecord;
		ShotPath* m_pkPath;
        // the current position
        vuVec3<double> m_vdPosition;
        // the current velocity
        vuVec3<double> m_vdVelocity;
		vuField<vpIsectorLOS*> m_isector;
    };

	BulletManager();
	~BulletManager(void);
	int Configure(void);
	BulletTracer* GetNextTracer(void);
	bool m_bDrawTracers;
	int m_iInactiveIndex;
	int m_iRoundsFired;
	int m_iGroupRoundsFired;
	// our tracer node
	vsGeometry* m_pkBulletNode;
	// our tracer geometry
	vrGeometry* m_pkGeometry;
	// our tracer render strategy
	vsRenderStrategyFrameGeometry* m_pkRenderStrategy;
	// the current state of the tracers
	vuVec3<double> m_vdWindVelocity;
	BulletTracer m_apTracer[MAX_NUM_TRACERS];
	vuList<BulletRecord*> m_lpkExpiredBullets;
	vuList<BulletTracer*> m_lpkActiveBullets;
	vuList<BulletTracer*> m_lpkAvailableBullets;
	vuList<ShotPath*> m_lpkShotPaths;

	static BulletManager* s_pkInstance;
};

#endif