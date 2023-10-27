#include <FactoryManager.h>
#include <MarineTarget.h>
#include <StationaryTarget.h>
#include <SteeringTarget.h>
#include <MarineSteeringTarget.h>
#include <HitRegion.h>
#include <SoundAmbient.h>
#include <SoundNode.h>
#include <SoundAttachedNode.h>
#include <FollowPathBehavior.h>


FactoryManager* FactoryManager::s_pkInstance = NULL;

FactoryManager::FactoryManager(void)
{

	m_mpkTargetFactories.insert(std::pair<CharPointer, Factory<ITarget>*>
									("MarineTarget", new MarineTargetFactory()));
	m_mpkTargetFactories.insert(std::pair<CharPointer, Factory<ITarget>*>
									("StationaryTarget", new StationaryTargetFactory()));
	m_mpkTargetFactories.insert(std::pair<CharPointer, Factory<ITarget>*>
									("SteeringTarget", new SteeringTargetFactory()));
	m_mpkTargetFactories.insert(std::pair<CharPointer, Factory<ITarget>*>
									("MarineSteeringTarget", new MarineSteeringTargetFactory()));
	m_mpkSoundFactories.insert(std::pair<CharPointer, Factory<ISound>*>
									("SoundAmbient", new SoundAmbientFactory()));
	m_mpkSoundFactories.insert(std::pair<CharPointer, Factory<ISound>*>
									("SoundNode", new SoundNodeFactory()));
	m_mpkSoundFactories.insert(std::pair<CharPointer, Factory<ISound>*>
									("SoundAttachedNode", new SoundAttachedNodeFactory()));
	m_mpkHitRegionFactories.insert(std::pair<CharPointer, Factory<IHitRegion>*>
									("HitRegion", new HitRegionFactory()));
	m_mpkSteeringBehaviorFactories.insert(std::pair<CharPointer, Factory<ISteeringBehavior>*>
									("FollowPathBehavior", new FollowPathBehaviorFactory()));

}

FactoryManager::~FactoryManager(void)
{
	vuMap<CharPointer, Factory<ITarget>*>::iterator kTargetIter = m_mpkTargetFactories.begin();

	for (kTargetIter; kTargetIter != m_mpkTargetFactories.end(); ++kTargetIter)
	{
		delete kTargetIter->second;
	}

	vuMap<CharPointer, Factory<ISound>*>::iterator kSoundIter = m_mpkSoundFactories.begin();

	for (kSoundIter; kSoundIter != m_mpkSoundFactories.end(); ++kSoundIter)
	{
		delete kSoundIter->second;
	}

	vuMap<CharPointer, Factory<IHitRegion>*>::iterator kRegionIter = m_mpkHitRegionFactories.begin();

	for (kRegionIter; kRegionIter != m_mpkHitRegionFactories.end(); ++kRegionIter)
	{
		delete kRegionIter->second;
	}
	
	vuMap<CharPointer, Factory<ISteeringBehavior>*>::iterator kSteerIter = m_mpkSteeringBehaviorFactories.begin();

	for (kSteerIter; kSteerIter != m_mpkSteeringBehaviorFactories.end(); ++kSteerIter)
	{
		delete kSteerIter->second;
	}
}