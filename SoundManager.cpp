#include <SoundManager.h>
#include <ALController.h>
#include <ALSound.h>
#include <ALBuffer.h>
#include <ALSource.h>
#include <AudioListener.h>
#include <SoundAmbient.h>
#include <SoundNode.h>
#include <ISound.h>
#include <FactoryManager.h>
#include <SoundAttachedNode.h>


SoundManager* SoundManager::s_pkInstance = NULL;

SoundManager::SoundManager(void)
{
	m_pkListener = new AudioListener();
}

SoundManager::~SoundManager(void)
{
	delete m_pkListener;

	Reset();

	vuMap<CharPointer, ISound*>::iterator kSoundIter = m_mpkAvailableSounds.begin();
	
	for (kSoundIter; kSoundIter != m_mpkAvailableSounds.end(); ++kSoundIter)
	{
		delete kSoundIter->second;
	}

	ALController::Shutdown();
}

void SoundManager::PlayAmbientSound(CharPointer sSound)
{
	ASSERT(m_mpkAvailableSounds.count(sSound))
	ASSERT((*(m_mpkAvailableSounds.find(sSound))).second)

	SoundAmbient* pkSound = (SoundAmbient*) (*(m_mpkAvailableSounds.find(sSound))).second;
	
	if (pkSound->ReleaseOnCompletion())
	{
		SoundAmbient* pkCopy = (SoundAmbient*) FactoryManager::GetInstance()->CreateSound("SoundAmbient");
		pkCopy->Copy(pkSound);
		pkCopy->Play();
		m_vpkPlayingSounds.push_back(pkCopy);
	}
	else
	{
		pkSound->Play();
	}
}

void SoundManager::PlayEnviromentalSound(CharPointer sSound, const vuVec3<double>& vdPos)
{
	ASSERT(m_mpkAvailableSounds.count(sSound))
	ASSERT((*(m_mpkAvailableSounds.find(sSound))).second)

	SoundNode* pkSound = (SoundNode*) (*(m_mpkAvailableSounds.find(sSound))).second;

	if (pkSound->ReleaseOnCompletion())
	{
		SoundNode* pkCopy = (SoundNode*) FactoryManager::GetInstance()->CreateSound("SoundNode");
		vsgu::copy<SoundNode>(pkCopy, pkSound);
		pkCopy->setTranslate(vdPos[0], vdPos[1], vdPos[2]);
		pkCopy->Play();
		m_vpkPlayingSounds.push_back(pkCopy);
	}
	else
	{
		pkSound->Play();
	}
}

void SoundManager::ClearSoundFromSource(ALSource* pkSource)
{
	vuList<ISound*>::iterator kIter = m_vpkPlayingSounds.begin();

	while (kIter != m_vpkPlayingSounds.end())
	{
		if ((*kIter)->GetSource() == pkSource)
		{
			ISound* pkSound = *kIter;
			m_vpkPlayingSounds.erase(kIter);
			delete pkSound;
			ASSERT(! pkSource->GetBuffersQueued())
			kIter = m_vpkPlayingSounds.end();
		}
		else
		{
			++kIter;
		}
	}
}

void SoundManager::Update(void)
{
	m_pkListener->Update();
	
	vuList<ISound*>::iterator kIter = m_vpkPlayingSounds.begin();

	while (kIter != m_vpkPlayingSounds.end())
	{
		if ((*kIter)->IsPlaying())
		{
			++kIter;
		}
		else
		{
			ISound* pkSound = *kIter;
			ALController::GetInstance()->FreeSource(pkSound->GetSource());
			delete pkSound;
			kIter = m_vpkPlayingSounds.erase(kIter);
		}
	}
}

void SoundManager::Reset(void)
{

	vuList<ISound*>::iterator kIter = m_vpkPlayingSounds.begin();

	for (kIter; kIter != m_vpkPlayingSounds.end(); ++kIter)
	{
		delete (*kIter);
	}
	
	m_vpkPlayingSounds.empty();
}

void SoundManager::Start(void)
{
	
}

const bool SoundManager::CheckForALError(void) const
{
	return ALController::GetInstance()->CheckForALError();
}

SoundAttachedNode* SoundManager::SpawnAttachedSound(CharPointer sSound, const char* sClassName)
{
	ASSERT(m_mpkAvailableSounds.count(sSound))

	SoundAttachedNode* pkAttachedNode = (SoundAttachedNode*) FactoryManager::GetInstance()->CreateSound(sClassName);

	ASSERT(pkAttachedNode)

	ISound* pkSound = m_mpkAvailableSounds.find(sSound)->second;

	ASSERT(pkSound)

	pkSound->PopulateAttachedSound(pkAttachedNode);

	return pkAttachedNode;
}