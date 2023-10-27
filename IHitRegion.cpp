#include <IHitRegion.h>
#include <vpFxParticleSystem.h>
#include <vsNode.h>
#include <AttachedParticleSystem.h> 
#include <ITarget.h>

#define NUM_THRESHOLDS 4

IHitRegion::IHitRegion(void) : m_iHitDecrement(1)
{
	m_kState = IHitRegion::UNDAMAGED;
}

IHitRegion::~IHitRegion(void)
{
	vuMap<RegionState, vuVector<AttachedParticleSystem*>*>::iterator kIter = m_mpkEffectsMap.begin();

	for (kIter; kIter != m_mpkEffectsMap.end(); ++kIter) 
	{
		vuVector<AttachedParticleSystem*>* pkVector = kIter->second;

		while (pkVector->size())
		{
			AttachedParticleSystem* pkSystem = pkVector->back();
			pkVector->pop_back();
			delete pkSystem;
		}

		delete pkVector;
	}
}

int IHitRegion::ProcessHit(ITarget* pkTarget)
{
	DecrementHitPoints(m_iHitDecrement);
	
	ASSERT(m_kState >= 2)

	RegionState kInitialState = m_kState; 

	while (m_iHitPoints <= m_aiHpThresholds[m_kState - 2] && m_kState < IHitRegion::DESTROYING)
	{
		m_kState = (RegionState) (m_kState + 1);
	}

	printf("Region HPs: %d\nRegion State: %d\n", m_iHitPoints, m_kState);

	if (kInitialState - m_kState)
	{
		if (m_mpkEffectsMap.count(m_kState))
		{
			vuVector<AttachedParticleSystem*>* pkVector = m_mpkEffectsMap.find(m_kState)->second;
		
			vuVector<AttachedParticleSystem*>::iterator kIter = pkVector->begin();

			for (kIter; kIter != pkVector->end(); ++kIter)
			{
				AttachedParticleSystem* pkSystem = *kIter;
				pkSystem->Activate(pkTarget->GetTargetObject());
				pkTarget->AddAttachedParticleSystem(pkSystem);
			}
		}

		vuList<AttachedParticleSystem*>::iterator kIter = pkTarget->GetAttachedParticleSystems().begin();

		while (kIter != pkTarget->GetAttachedParticleSystems().end())
		{
			if ((*kIter)->CheckToDeactivate((unsigned int) ITarget::UNSET, (unsigned int) m_kState))
			{
				kIter = pkTarget->GetAttachedParticleSystems().erase(kIter);
			}

			else
			{
				++kIter;
			}
		}

		pkTarget->FlagStateChange();
		return m_iAreaHitPointValue;
	}

	return 0;
}

void IHitRegion::InstanceHitRegion(IHitRegion* pkRegion)
{
	m_iStartingHitPoints = pkRegion->GetStartingHitPoints();
	m_iHitPoints = pkRegion->GetHitPoints();
	m_iHitDecrement = pkRegion->GetHitDecrement();
	m_iAreaHitPointValue = pkRegion->GetAreaHitPointValue();
	m_kState = pkRegion->GetState();
	SetSurfaceType(pkRegion->GetSurfaceType());

	vuMap<RegionState, vuVector<AttachedParticleSystem*>*>::iterator kIter = pkRegion->m_mpkEffectsMap.begin();

	for (kIter; kIter != pkRegion->m_mpkEffectsMap.end(); ++kIter)
	{
		vuVector<AttachedParticleSystem*>* pkVector = new vuVector<AttachedParticleSystem*>();
		
		vuVector<AttachedParticleSystem*>::iterator kEffectIter = kIter->second->begin();

		for (kEffectIter; kEffectIter != kIter->second->end(); ++kEffectIter)
		{
			AttachedParticleSystem* pkSystem = new AttachedParticleSystem();
			pkSystem->InstanceParticleSystem(*kEffectIter);
			pkVector->push_back(pkSystem);
		}

		m_mpkEffectsMap.insert(std::pair<RegionState, vuVector<AttachedParticleSystem*>*>(kIter->first, pkVector));

	}

	for (int i = 0; i < NUM_THRESHOLDS; ++i)
	{
		m_aiHpThresholds[i] = pkRegion->m_aiHpThresholds[i];
	}
}

void IHitRegion::Reset(void)
{
	m_iHitPoints = m_iStartingHitPoints;
	m_kState = IHitRegion::UNDAMAGED;
}