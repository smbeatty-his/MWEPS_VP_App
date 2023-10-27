#include <ALController.h>
#include <al.h>
#include <alc.h>
#include <AL\alut.h>
#include <ALSource.h>
#include <ALBuffer.h>
#include <ALListener.h>

ALController* ALController::s_pkInstance = NULL;

ALController::ALController(int* argc, char *argv[]) : m_uiBuffersAvailable(MAX_AUDIO_BUFFERS)
{
	ALboolean bSuccess = alutInit(argc, argv);
	ASSERT(bSuccess)

	Configure();
}

ALController::~ALController(void)
{
	StopAllSounds();
	alDeleteSources(MAX_AUDIO_SOURCES, m_pkSources);
	alDeleteBuffers(MAX_AUDIO_BUFFERS, m_pkBuffers);

	while (m_vpkAvailableSources.size())
	{
		ALSource* pkSource = m_vpkAvailableSources.back();
		m_vpkAvailableSources.pop_back();
		delete pkSource;
	}

	while (m_vpkUsedSources.size())
	{
		ALSource* pkSource = m_vpkUsedSources.back();
		m_vpkUsedSources.pop_back();
		delete pkSource;
	}
	
}

void ALController::Configure(void)
{
	alGenBuffers(MAX_AUDIO_BUFFERS, m_pkBuffers);
	alGenSources(MAX_AUDIO_SOURCES, m_pkSources);
	
	for (int i = 0; i < MAX_AUDIO_SOURCES; ++i)
	{
		m_vpkAvailableSources.push_back(new ALSource(m_pkSources[i]));
	}
}

ALBuffer* ALController::LoadSound(const char* sFileName)
{
	ASSERT(sFileName)
	ASSERT(m_uiBuffersAvailable)

	m_pkBuffers[m_uiBuffersAvailable - 1] = alutCreateBufferFromFile(sFileName);

	--m_uiBuffersAvailable;
	ASSERT(! CheckForAlutError())

	return new ALBuffer(m_pkBuffers[m_uiBuffersAvailable]);
}

const bool ALController::CheckForAlutError(void) const
{
	ALenum kErrCode = alutGetError();
	if (! kErrCode) 
	{ 
		return false; 
	}
	else
	{
		printf("ERROR: Alut Error: %s\n", alutGetErrorString(kErrCode));
		return true;
	}
}

const bool ALController::CheckForALError(void) const
{
	ALenum kErrCode = alGetError();
	if (! kErrCode) 
	{ 
		return false; 
	}
	else
	{
		printf("ERROR: AL Error: %s\n", alGetString(kErrCode));
		return true;
	}
}

ALSource* ALController::GetAvailableSource(void)
{
	ALSource* pkSource = NULL;

	if (m_vpkAvailableSources.size())
	{
		pkSource = m_vpkAvailableSources.back();
		m_vpkAvailableSources.pop_back();
		m_vpkUsedSources.push_back(pkSource);
	}

	else
	{	
		std::list<ALSource*>::iterator kIter = m_vpkUsedSources.begin();
		
		while (kIter != m_vpkUsedSources.end())
		{
			if (! (*kIter)->IsReserved())
			{
				pkSource = *kIter;
				m_vpkUsedSources.push_back(pkSource);
				kIter = m_vpkUsedSources.erase(kIter);
				kIter = m_vpkUsedSources.end();
			}
			else
			{
				++kIter;
			}
		}
	}

	ASSERT(pkSource)

	return pkSource;
}

void ALController::FreeSource(ALSource* pkSource)
{
	ASSERT(pkSource)

	std::list<ALSource*>::iterator kIter = m_vpkUsedSources.begin();

	while (kIter != m_vpkUsedSources.end())
	{
		if (*kIter == pkSource)
		{
			m_vpkUsedSources.erase(kIter);
			kIter = m_vpkUsedSources.end();
		}
		else
		{
			++kIter;
		}
	}

	m_vpkAvailableSources.push_back(pkSource);
}

void ALController::StopAllSounds(void)
{
	std::list<ALSource*>::iterator kIter = m_vpkUsedSources.begin();

	for (kIter; kIter != m_vpkUsedSources.end(); ++kIter)
	{
		(*kIter)->Stop();
	}
}