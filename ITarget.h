#ifndef TARGET_MODULE_H
#define TARGET_MODULE_H

#include <vuVec3.h>
#include <vuMap.h>
#include <vuBase.h>
#include <vpObject.h>
#include <CharPointer.h>
#include <Factory.h>
#include <IHitRegion.h>
#include <vuVector.h>

#define PATH_UNSET -1

///////////////////////////////////////////////////////////////////////////////
///
/// @class ITarget
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class vsNode;
class AttachedParticleSystem;
class SteeringController;
class vpPathWayPointSet;
class SoundAttachedNode;
class ISteeringBehavior;
class IBehaviorState;
class TargetRecord;

class ITarget
{
public:

	enum TargetState
	{
		UNSET,				// 0
		INACTIVE,			// 1
		UNDAMAGED,			// 2
		LIGHT_DAMAGE,		// 3
		MEDIUM_DAMAGE,		// 4
		HEAVY_DAMAGE,		// 5
		DESTROYING,			// 6
		DESTROYED,			// 7
		DETONATED,			// 8
		INVALID				// 9
	};

	virtual ~ITarget(void);
	inline void SetStartPosition(const vuVec3<double>& vfStartPos) { m_vfStartPosition = vfStartPos; }; 
	inline const vuVec3<double>& GetStartPosition(void) const { return m_vfStartPosition; }
	inline void SetStartRotation(const vuVec3<double>& vfStartRot) { m_vfStartRotation = vfStartRot; }; 
	inline const vuVec3<double>& SetStartRotation(void) const { return m_vfStartPosition; }
	virtual int Configure() = 0;
	virtual void Update(const double dTime);
	virtual void PopulateTarget(const char* sTargetName) = 0;
	virtual void Reset(void);
	virtual void InstanceTarget(ITarget* pkTarget, const char* sInstanceName);
	virtual void ProcessHit(const char* sRegionName, const vuVec3<double>& vdHitPos);
	virtual inline const char* GetClassname(void) const = 0;
	// SMB WAS: virtual inline void SetTargetedObject(vpObject* pkObject) { m_pkObject = pkObject; };
	//    changed to avoid warning C4100 unreferenced formal parameter
	virtual inline void SetTargetedObject(vpObject* pkObject) { m_pkObject = pkObject; };
	virtual inline vuVec3<double>* GetTargetedPoint(void) { return NULL; }
	const char* GetName(void) const;
	void SetName(const char* sName);
	void ProcessStateChange(void);

	inline const double GetStartTime(void) const { return m_dStartTime; }
	inline const void SetStartTime(const double dStartTime) { m_dStartTime = dStartTime; }
	inline const int GetHitPoints(void) const { return m_iHitPoints; }
	inline const void SetHitPoints(const int iHitPoints) { m_iHitPoints = iHitPoints; }
	inline const int GetStartingHitPoints(void) { return m_iStartingHitPoints; }
	inline const void SetStartingHitPoints(const int iHPs) { m_iStartingHitPoints = iHPs; } 
	const inline int GetHitDecrement(void) const { return m_iHitDecrement; }
	const inline void SetHitDecrement(const int iDecrement) { m_iHitDecrement = iDecrement; }
	inline const double GetMaxSpeed(void) const { return m_dMaxSpeed; }
	inline const void SetMaxSpeed(const double dSpeed) { m_dMaxSpeed = dSpeed; }
	inline const double GetMaxForce(void) const { return m_dMaxForce; }
	inline const void SetMaxForce(const double dForce) { m_dMaxForce = dForce; }
	const inline void SetState(const TargetState& kState) { m_kState = kState; }
	const inline TargetState& GetState(void) { return m_kState; }
	const inline vpPathWayPointSet* GetActiveWayPointSet(void) const
	{
		if (m_iPathIndex == PATH_UNSET)
		{
			return NULL;
		}
		else
		{
			vuList<vpPathWayPointSet*>::const_iterator kIter = m_lpkWayPointSets.begin();

			ASSERT(m_iPathIndex < m_lpkWayPointSets.size())

			for (int i = 0; i < m_iPathIndex; ++i)
			{
				++kIter;
			}
			
			return *kIter;
		}
	}
	const inline void SetActiveWayPointSet(const int iIndex) { m_iPathIndex = iIndex;}
	const inline void SetStartingWayPointSet(const int iIndex) { m_iStartingPathIndex = iIndex; }
	const inline void AttachWayPointSet(vpPathWayPointSet* pkWayPointSet)
	{
		ASSERT(pkWayPointSet)

		m_lpkWayPointSets.push_back(pkWayPointSet);
	}

	const inline int GetWayPointIndex(void) const { return m_iWayPointIndex; }
	const inline void SetWayPointIndex(const int iIndex) { m_iWayPointIndex = iIndex; }
	const inline void SetStartingWayPointIndex(const int iIndex) { m_iStartingWayPointIndex = iIndex; }

	const void AddAttachedParticleSystem(AttachedParticleSystem* pkSystem);
	const void RemoveAttachedParticleSystem(AttachedParticleSystem* pkSystem);
	inline vuList<AttachedParticleSystem*>& GetAttachedParticleSystems(void) { return m_lpkAttachedEffects; } 

	inline vuList<SoundAttachedNode*>& GetAttachedSounds(void) { return m_lpkAttachedSounds; }

	const void AddAttachedSound(SoundAttachedNode* pkSound);

	const void AddSound(SoundAttachedNode* pkSound);

	inline const void SetEffectMap(const vuMap<TargetState, vuVector<AttachedParticleSystem*>*>& pkMap) 
	{ 
		m_mpkStateEffectMap = pkMap; 
	}

	inline const vuMap<TargetState, vuVector<AttachedParticleSystem*>*>& GetEffectMap(void) const 
	{ 
		return m_mpkStateEffectMap; 
	}

	inline const void SetSoundMap(const vuMap<TargetState, vuVector<SoundAttachedNode*>*>& pkMap)
	{
		m_mpkStateSoundMap = pkMap;
	}

	inline const vuMap<TargetState, vuVector<SoundAttachedNode*>*>& GetSoundMap(void) const
	{
		return m_mpkStateSoundMap;
	}

	inline const vuMap<CharPointer, IHitRegion*>& GetRegionMap(void) const { return m_mpkRegionMap; }

	inline vpObject* GetTargetObject(void) const { return m_pkObject; }
	inline const void SetTargetObject(vpObject* pkObject) 
	{
		ASSERT(pkObject)
		ASSERT(! m_pkObject)
		m_pkObject = pkObject; 
	}
	
	const inline bool GetClone(void) const { return m_bClone; }
	const inline void SetHitPointThreshold(const int iHPs, const int iIndex) { m_aiHpThresholds[iIndex] = iHPs; }
	const inline void AddHitRegion(CharPointer sRegionName, IHitRegion* pkRegion) 
	{
		ASSERT(pkRegion)
		m_mpkRegionMap.insert(std::pair<CharPointer, IHitRegion*>(sRegionName, pkRegion));
	}

	const inline vuVec3<double>& GetVelocity(void) const { return m_vdVelocity; }
	const inline void SetVelocity(const vuVec3<double>& vdVelocity) { m_vdVelocity = vdVelocity; }
	const vuVec3<double> GetCenterOfMass(void) const;
	inline void SetCenterOfMassOffset(const vuVec3<double>& vdOffset) { m_vdCenterOfMassOffset = vdOffset; }
	const inline vuVec3<double>& GetCenterOfMassOffset(void) const { return m_vdCenterOfMassOffset; }

	const vuVec2<double> GetCOMScreenCoordinates(const vuVec3<double>& vdCenterOfMass) const; 

	const inline double GetDecelerationRate(void) const { return m_dDecelerationRate; }
	const inline void SetDecelerationRate(const double dRate) { m_dDecelerationRate = dRate; }

	const inline vuList<TargetRecord*>& GetTargetRecords(void) const { return m_lpkTargetRecords; }

	void AddSteeringBehavior(ISteeringBehavior* pkBehavior);

	void UpdateVelocity(const double dTime);
	void UpdateTranslate(const double dTime);
	void UpdateTargetRecord();
	inline void AddTargetRecord(TargetRecord* pkRecord) { m_lpkTargetRecords.push_back(pkRecord); }
	void ClearTargetRecords(void);

	void FlagStateChange(void) { m_bLogStateChange = true; }

protected:
	
	ITarget(void);
	const inline void MarkAsClone(void) { m_bClone = true; }
	SteeringController* m_pkSteeringController;
	IBehaviorState* m_pkBehaviorState;
	bool m_bLogStateChange;

private:
	
	bool m_bClone;
	int m_iHitPoints;
	int m_iStartingHitPoints;
	int m_iHitDecrement;
	int m_iPathIndex;
	int m_iStartingPathIndex;
	int m_iWayPointIndex;
	int m_iStartingWayPointIndex;
	double m_dMaxSpeed;
	double m_dMaxForce;
	double m_dDecelerationRate;
	double m_dStartTime;
	int m_aiHpThresholds[4];
	vpObject* m_pkObject;
	TargetState m_kState;
	vuVec3<double> m_vfStartPosition;
	vuVec3<double> m_vfStartRotation;
	vuVec3<double> m_vdVelocity;
	vuVec3<double> m_vdCenterOfMassOffset;
	vuMap<TargetState, vuVector<AttachedParticleSystem*>*> m_mpkStateEffectMap;
	vuMap<TargetState, vuVector<SoundAttachedNode*>*> m_mpkStateSoundMap;
	vuMap<CharPointer, IHitRegion*> m_mpkRegionMap;
	vuList<AttachedParticleSystem*> m_lpkAttachedEffects;
	vuList<SoundAttachedNode*> m_lpkAttachedSounds;
	vuList<vpPathWayPointSet*> m_lpkWayPointSets;
	vuList<TargetRecord*> m_lpkTargetRecords;
};

#endif