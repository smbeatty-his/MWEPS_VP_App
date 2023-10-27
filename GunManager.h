#ifndef GUN_MANAGER_MODULE_H
#define GUN_MANAGER_MODULE_H

#include <DebugUtil.h>
#include <vuVec3.h>

class IFiringMode;

///////////////////////////////////////////////////////////////////////////////
///
/// @class GunManager
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class GunManager
{

public:

	enum FireType
	{
		UNSET,
		SINGLE_SHOT,
		BURST,
		AUTO,
		UNDEFINED
	};

	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new GunManager();
	}

	static inline GunManager* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		delete s_pkInstance;
	}

	void Configure(void);
	void Fire(void);
	void Update(double dDeltaTime);
	void Reset(void);
	void Start(void);
	void GetMouseHeadingPitch(double* dHeading, double* dPitch, vuVec3<double>* pvdDirVec);
	void GetHeadingPitchFromMouseCoordinates(double* dHeading, double* dPitch, float fMX, float fMY, 
														vuVec3<double>* pvdDirVec);
	void PlayGunfireSound(void);
	void GetMousePixelCoordinates(float* fMX, float* fMY);
	void SetLagAdjustmentPoint(void);
	void UpdateLagAdjustmentPoint(void);
	void TriggerReleased(void);
	inline const vuVec3<double>& GetLagAdjustmentPoint(void) const { return m_vdMotionPlatformAdjustmentPoint; }

	const inline FireType& GetFireType(void) const { return m_kFireType; }
	const inline void SetFireType(const FireType& kFireType) { m_kFireType = kFireType; }   

private:

	GunManager(void);
	~GunManager(void);
	static GunManager* s_pkInstance;
	FireType m_kFireType;
	IFiringMode* m_pkFiringMode;
	vuVec3<double> m_vdMotionPlatformAdjustmentPoint;
};


#endif