#ifndef AIM_MANAGER_MODULE_H
#define AIM_MANAGER_MODULE_H

#include <DebugUtil.h>
#include <vuList.h>
#include <vuMatrix.h>
#include <vuVec2.h>
#include <vpIsectorLOS.h>
#include "vpOverlay2DImage.h"

class AimRecord;
class vpInputMouse;
class vpOverlay2DImage;

typedef struct WMEvnt WMEvent;

#define SCREEN_WIDTH_CENTER 960.0f
#define SCREEN_HEIGHT_CENTER 600.0f

///////////////////////////////////////////////////////////////////////////////
///
/// @class AimManager
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class AimManager
{

public:

	static inline AimManager* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Initialize(int iPulseRate = 10)
	{
		ASSERT(! s_pkInstance);
		s_pkInstance = new AimManager(iPulseRate);
	}

	static inline void Shutdown(void)
	{
		ASSERT(s_pkInstance)
		delete s_pkInstance;
	}

	inline void SetMouse(vpInputMouse* pkMouse) { m_pkMouse = pkMouse; }
	// SMB was: const inline vpOverlay2DImage* GetCrosshair(void) { return m_pkCrosshair; }
	vpOverlay2DImage* GetCrosshair(void) { return m_pkAimCrosshair; } 
	void SetCrosshair();

	vuList<AimRecord*>& GetAimRecords(void) { return m_lpkAimRecords; }
	inline void AddAimRecord(AimRecord* pkRecord) { m_lpkAimRecords.push_back(pkRecord); }
	void ClearAimRecords(void);
	void PushAim(const WMEvent& kEvent, const double dReceiveTime);
	// SMB 06Nov2023 - We don't call this anymore. Crosshair responds to Laser spot, handled with PushAim
	//void UpdateCrosshairPosition(const WMEvent& kEvent);
	void Update(double dDeltaTime);
	void Reset(void);
	void Start(void);
	void GetScreenCoordinates(float* fX, float* fY);

private:

	vuField<vpIsectorLOS*> m_kIsector;
	AimManager(int iPulseRate);
	~AimManager(void);
	bool m_bFixedViewMode;
	vpInputMouse* m_pkMouse;
	vpOverlay2DImage* m_pkCrosshair;
	vpOverlay2DImage* m_pkAimCrosshair;
	int m_iAimPulseRate;
	double m_dAimPulseDelay;
	double m_dAimDelayedTime;
	vuVec2<float> m_vfCrosshairAdjustment;
	vuList<AimRecord*> m_lpkAimRecords;
	static AimManager* s_pkInstance;
};

#endif