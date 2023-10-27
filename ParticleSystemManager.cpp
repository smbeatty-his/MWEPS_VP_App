#include <vpFxParticleSystem.h>
#include <ParticleSystemManager.h>
#include <DebugUtil.h>
#include <vsNode.h>

ParticleSystemManager* ParticleSystemManager::s_pkInstance = NULL;

ParticleSystemManager::ParticleSystemManager(void)
{
	
}

ParticleSystemManager::~ParticleSystemManager(void)
{
	Reset();

	vuMap<CharPointer, vpFxParticleSystem*>::iterator kMapIter = m_mpkEffectsMap.begin();

	for (kMapIter; kMapIter != m_mpkEffectsMap.end(); ++kMapIter)
	{
		kMapIter->second->unref();
	}

	m_mpkEffectsMap.clear();
}

void ParticleSystemManager::Update()
{
	vuList<vpFxParticleSystem*>::iterator kIter = m_vpkParticleSystems.begin();

	while (kIter != m_vpkParticleSystems.end())
	{
		vpFxParticleSystem* pkSystem = *kIter;

		if (pkSystem->getElapsedDuration() >= pkSystem->getOverallDuration())
		{
			kIter = m_vpkParticleSystems.erase(kIter);
			(*vpScene::begin())->removeChild(pkSystem);

			pkSystem->unref();
		}

		else
		{
			++kIter;
		}
	}
}

void ParticleSystemManager::AddParticleSystem(CharPointer sName, const vuVec3<double>& vdPos)
{
	ASSERT(m_mpkEffectsMap.count(sName))
	ASSERT((*(m_mpkEffectsMap.find(sName))).second)

	vpFxParticleSystem* pkEffect = new vpFxParticleSystem();
	ASSERT(pkEffect)

	vpFxParticleSystem* pkMasterEffect = (*(m_mpkEffectsMap.find(sName))).second;
	ASSERT(pkMasterEffect)

	vsgu::copy<vpFxParticleSystem>(pkEffect, pkMasterEffect);

	pkEffect->setTranslate(vdPos[0], vdPos[1], vdPos[2]);
	pkEffect->configure();
	pkEffect->setEnable(true);
	pkEffect->ref();

	(*vpScene::begin())->push_back_child(pkEffect);

	m_vpkParticleSystems.push_back(pkEffect);
}

void ParticleSystemManager::RegisterParticleSystem(CharPointer sName, vpFxParticleSystem* pkSystem)
{
	ASSERT(pkSystem)

	pkSystem->ref();
	pkSystem->configure();
	pkSystem->setEnable(false);
	pkSystem->setIsectMask(0);
	pkSystem->ref();

	m_mpkEffectsMap.insert(std::pair<CharPointer, vpFxParticleSystem*>(sName, pkSystem));
}

vpFxParticleSystem* ParticleSystemManager::SpawnParticleSystem(CharPointer sName)
{
	ASSERT(m_mpkEffectsMap.count(sName))
	ASSERT((*(m_mpkEffectsMap.find(sName))).second)

	vpFxParticleSystem* pkEffect = new vpFxParticleSystem();
	ASSERT(pkEffect)

	vpFxParticleSystem* pkMasterEffect = (*(m_mpkEffectsMap.find(sName))).second;
	ASSERT(pkMasterEffect)

	vsgu::copy<vpFxParticleSystem>(pkEffect, pkMasterEffect);
	pkEffect->configure();
	pkEffect->setEnable(false);
	pkEffect->ref();

	return pkEffect;
}

void ParticleSystemManager::Reset(void)
{
	vuList<vpFxParticleSystem*>::iterator kIter = m_vpkParticleSystems.begin();

	while (kIter != m_vpkParticleSystems.end())
	{
		vpFxParticleSystem* pkSystem = *kIter;
		pkSystem->unref();
		pkSystem->setEnable(false);
		kIter = m_vpkParticleSystems.erase(kIter);
	}
}

void ParticleSystemManager::Start(void)
{

}