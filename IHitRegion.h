#ifndef IHIT_REGION_MODULE_H
#define IHIT_REGION_MODULE_H

#include <vuMap.h>
#include <Factory.h>
#include <vuVector.h>
#include <vuVec3.h>

class vpFxParticleSystem;
class vsNode;
class AttachedParticleSystem;
class ITarget;

class IHitRegion
{
public:

	enum RegionState
	{
		UNSET,				// 0
		INACTIVE,			// 1
		UNDAMAGED,			// 2
		LIGHT_DAMAGE,		// 3
		MEDIUM_DAMAGE,		// 4
		HEAVY_DAMAGE,		// 5
		DESTROYING,			// 6
		DESTROYED,			// 7
		INVALID				// 8
	};

	IHitRegion();
	virtual ~IHitRegion();
	virtual int ProcessHit(ITarget* pkTarget);
	virtual const char* GetClassName(void) const = 0;

	const inline int GetHitPoints(void) { return m_iHitPoints; }
	const inline void SetHitPoints(const int iHPs) { m_iHitPoints = iHPs; }
	const inline int GetStartingHitPoints(void) { return m_iStartingHitPoints; }
	const inline void SetStartingHitPoints(const int iHPs) { m_iStartingHitPoints = iHPs; }
	const inline int GetAreaHitPointValue(void) { return m_iAreaHitPointValue; }
	const inline void SetAreaHitPointValue(const int iValue) { m_iAreaHitPointValue = iValue; }

	const inline void DecrementHitPoints(const int iHPs = 1) 
	{ 
		m_iHitPoints = ((m_iHitPoints - iHPs) > 0) ? (m_iHitPoints - iHPs) : 0;
	}
	
	const inline RegionState GetState(void) const { return m_kState; }
	const inline void SetState(const RegionState kState) { m_kState = kState; }

	const inline vuMap<RegionState, vuVector<AttachedParticleSystem*>*>& GetEffectMap(void) const
	{
		return m_mpkEffectsMap;
	}

	const inline void SetEffectMap(const vuMap<RegionState, vuVector<AttachedParticleSystem*>*>& kMap)
	{
		m_mpkEffectsMap = kMap;
	}

	const inline char* GetSurfaceType(void) const { return m_sSurfaceType; }
	const inline void SetSurfaceType(const char* sType) { strcpy(m_sSurfaceType, sType); }

	const inline int GetHitDecrement(void) const { return m_iHitDecrement; }
	const inline void SetHitDecrement(const int iDecrement) { m_iHitDecrement = iDecrement; }

	const inline void SetHitPointThreshold(const int iHPs, const int iIndex) { m_aiHpThresholds[iIndex] = iHPs; }

	virtual void InstanceHitRegion(IHitRegion* pkRegion);
	virtual void Reset(void);

protected:
	vuMap<RegionState, vuVector<AttachedParticleSystem*>*> m_mpkEffectsMap;
	int m_aiHpThresholds[4];

private:
	int m_iStartingHitPoints;
	int m_iHitPoints;
	int m_iHitDecrement;
	int m_iAreaHitPointValue;
	RegionState m_kState;
	char m_sSurfaceType[32];
};

#endif