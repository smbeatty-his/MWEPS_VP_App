#ifndef FACTORY_MANAGER_MODULE_H
#define FACTORY_MANAGER_MODULE_H

#include <DebugUtil.h>
#include <vuVector.h>
#include <vuMap.h>
#include <Factory.h>
#include <ITarget.h>
#include <IHitRegion.h>
#include <ISound.h>
#include <ISteeringBehavior.h>

class FactoryManager
{
public:

	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new FactoryManager();
	}

	static inline FactoryManager* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		ASSERT(s_pkInstance)
		delete s_pkInstance;
	}

	inline ITarget* CreateTarget(CharPointer sClassName) const
	{
		ASSERT(m_mpkTargetFactories.count(sClassName))
		ASSERT(m_mpkTargetFactories.find(sClassName)->second)

		return m_mpkTargetFactories.find(sClassName)->second->Create();
	}

	inline ISound* CreateSound(CharPointer sClassName) const
	{
		ASSERT(m_mpkSoundFactories.count(sClassName))
		ASSERT(m_mpkSoundFactories.find(sClassName)->second)

		return m_mpkSoundFactories.find(sClassName)->second->Create();
	}

	inline IHitRegion* CreateHitRegion(CharPointer sClassName) const
	{
		ASSERT(m_mpkHitRegionFactories.count(sClassName))
		ASSERT(m_mpkHitRegionFactories.find(sClassName)->second)

		return m_mpkHitRegionFactories.find(sClassName)->second->Create();
	}

	inline ISteeringBehavior* CreateSteeringBehavior(CharPointer sClassName) const
	{
		ASSERT(m_mpkSteeringBehaviorFactories.count(sClassName))
		ASSERT(m_mpkSteeringBehaviorFactories.find(sClassName)->second)

		return m_mpkSteeringBehaviorFactories.find(sClassName)->second->Create();
	}

private:
	
	FactoryManager(void);
	~FactoryManager(void);
	static FactoryManager* s_pkInstance;
	vuMap<CharPointer, Factory<ITarget>*> m_mpkTargetFactories;
	vuMap<CharPointer, Factory<ISound>*> m_mpkSoundFactories;
	vuMap<CharPointer, Factory<IHitRegion>*> m_mpkHitRegionFactories;
	vuMap<CharPointer, Factory<ISteeringBehavior>*> m_mpkSteeringBehaviorFactories;
};

#endif