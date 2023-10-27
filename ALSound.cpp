#include <al.h>
#include <DebugUtil.h>
#include <ALController.h>
#include <ALSource.h>
#include <ALBuffer.h>
#include <ALSound.h>
#include <SoundManager.h>


ALSound::ALSound(bool bRelease) : m_pkBuffer(NULL), m_pkSource(NULL), m_fMinGain(0.0f), m_fMaxGain(1.0f),
								  m_fGain(1.0f), m_fPitch(1.0f),
								  m_bRelease(bRelease), m_bLooping(false)
{
	
}

ALSound::~ALSound(void)
{
	if (m_pkSource && m_pkBuffer)
	{
		m_pkSource->Stop();
		ASSERT(m_pkSource->GetBuffersQueued())
		ALuint uiBuffer = m_pkBuffer->GetBuffer();
		m_pkSource->UnqueueBuffers(1, &uiBuffer);
		ASSERT(! m_pkSource->GetBuffersQueued())
	}
}

void ALSound::LoadSound(const char* sFilename)
{
	SetBuffer(ALController::GetInstance()->LoadSound(sFilename));
}

void ALSound::Play(void)
{
	ASSERT(m_pkBuffer)

	if (! m_pkSource)
	{
		SetSource(ALController::GetInstance()->GetAvailableSource());

		if (m_pkSource->GetBuffersQueued())
		{
			SoundManager::GetInstance()->ClearSoundFromSource(m_pkSource);
		}

		ConfigureSource();
		
		ALuint uiBuffer = m_pkBuffer->GetBuffer();
		
		ASSERT(! m_pkSource->GetBuffersQueued())

		m_pkSource->QueueBuffers(1, &(uiBuffer));
	}

	m_pkSource->Play();
}

void ALSound::ConfigureSource(void)
{
	m_pkSource->SetLooping(m_bLooping);
	m_pkSource->SetGain(m_fGain);
	m_pkSource->SetPitch(m_fPitch);
	m_pkSource->SetMaxGain(m_fMinGain);
	m_pkSource->SetMaxGain(m_fMaxGain);
	m_pkSource->SetReserved(! m_bRelease);
}

const bool ALSound::IsPlaying(void) const
{
	ALint iState = GetSource()->GetSourceState();
	return (iState == AL_PLAYING);
}

