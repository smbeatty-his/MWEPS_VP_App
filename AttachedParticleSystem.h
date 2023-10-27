#ifndef ATTACHED_PARTICLE_SYSTEM_MODULE_H
#define ATTACHED_PARTICLE_SYSTEM_MODULE_H

#include <DebugUtil.h>
#include <vuVec3.h>
#include <vuMatrix.h>

class vpFxParticleSystem;
class vpObject;
class ITarget;

class AttachedParticleSystem
{

public:
	
	AttachedParticleSystem(void);
	~AttachedParticleSystem(void);
	void Update(vpObject* pkObject);
	void Activate(vpObject* pkObject);
	bool CheckToDeactivate(unsigned int uiTargetState, unsigned int uiRegionState);
	void InstanceParticleSystem(AttachedParticleSystem* pkSystem);

	const inline vuVec3<double>& GetOffset(void) const { return m_vdOffset; }
	const inline void SetOffset(const vuVec3<double>& vdOffset) { m_vdOffset = vdOffset; }
	inline vpFxParticleSystem* GetParticleSystem(void) const { return m_pkSystem; }
	const void SetParticleSystem(vpFxParticleSystem* pkSystem);
	const inline unsigned int GetTargetEndState(void) const { return m_uiEndTargetState; }
	const inline void SetTargetEndState(const unsigned int uiState) { m_uiEndTargetState = uiState; }
	const inline unsigned int GetRegionEndState(void) const { return m_uiEndRegionState; }
	const inline void SetRegionEndState(const unsigned int uiState) { m_uiEndRegionState = uiState; }

private:
	
	vpFxParticleSystem* m_pkSystem;
	vuVec3<double> m_vdOffset;
	unsigned int m_uiEndTargetState;
	unsigned int m_uiEndRegionState;

};

#endif