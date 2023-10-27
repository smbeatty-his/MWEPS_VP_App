#ifndef TARGET_RECORD_MODULE_H
#define TARGET_RECORD_MODULE_H

#include <vuVec3.h>
#include <ITarget.h>
#include <IHitRegion.h>

class TargetRecord
{
public:

	TargetRecord(void);
	~TargetRecord(void);
	const inline vuVec3<double>& GetPosition(void) const { return m_vdPosition; }
	const inline void SetPosition(const vuVec3<double>& vdPos) { m_vdPosition = vdPos; }
	const inline vuVec3<double>& GetRotation(void) const { return m_vdRotation; }
	const inline void SetRotation(const vuVec3<double>& vdRot) { m_vdRotation = vdRot; }
	const inline double& GetTime(void) const { return m_dTime; }
	const inline void SetTime(const double& dTime) { m_dTime = dTime; }
	const inline ITarget::TargetState& GetState(void) const { return m_kState; } 
	const inline void SetState(const ITarget::TargetState& kState) { m_kState = kState; }
	inline void AddRegionState(const IHitRegion::RegionState& kState) { m_lkHitRegionStates.push_back(kState); }
	const inline vuVec3<double>& GetCenterOfMass(void) { return m_vdCenterOfMass; }
	inline void SetCenterOfMass(const vuVec3<double>& vdCenterOfMass) { m_vdCenterOfMass = vdCenterOfMass; }
	void Serialize(FILE* pkLogFile);
	void Deserialize(FILE* pkLogFile);
	const inline vuVec2<double>& GetCOMScreenCoordinates(void) const { return m_vdCOMScreenCoordinates; }
	inline void SetCOMScreenCoordinates(const vuVec2<double>& vdScreenCoords) { m_vdCOMScreenCoordinates = vdScreenCoords; }
 
private:

	double m_dTime;
	ITarget::TargetState m_kState;
	vuList<IHitRegion::RegionState> m_lkHitRegionStates;
	vuVec2<double> m_vdCOMScreenCoordinates;
	vuVec3<double> m_vdPosition;
	vuVec3<double> m_vdRotation;
	vuVec3<double> m_vdCenterOfMass;
};

#endif