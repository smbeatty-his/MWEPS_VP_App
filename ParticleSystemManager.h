#ifndef PARTICLE_SYSTEM_MANAGER_MODULE_H
#define PARTICLE_SYSTEM_MANAGER_MODULE_H

#include <DebugUtil.h>
#include <CharPointer.h>
#include <vuList.h>
#include <vuMap.h>
#include <vuVec3.h>

class vpFxParticleSystem;

///////////////////////////////////////////////////////////////////////////////
///
/// @class ParticleSystemManager
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class ParticleSystemManager
{
public:
	
	void AddParticleSystem(CharPointer sName, const vuVec3<double>& vdPos);
	void RegisterParticleSystem(CharPointer sName, vpFxParticleSystem* pkSystem);
	vpFxParticleSystem* SpawnParticleSystem(CharPointer sName);
	void Update(void);
	void Reset(void);
	void Start(void);

	inline static void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new ParticleSystemManager();
	}
	inline static ParticleSystemManager* GetInstance(void) 
	{ 
		ASSERT(s_pkInstance)
		return s_pkInstance; 
	}
	inline static void Shutdown(void)
	{
		delete s_pkInstance;
	}

private:

	vuList<vpFxParticleSystem*> m_vpkParticleSystems;
	vuMap<CharPointer, vpFxParticleSystem*> m_mpkEffectsMap;
	ParticleSystemManager(void);
	~ParticleSystemManager(void);
	static ParticleSystemManager* s_pkInstance;
};

#endif