#ifndef AL_CONTROLLER_MODULE_H
#define AL_CONTROLLER_MODULE_H

#include <DebugUtil.h>
#include <vector>
#include <list>

typedef unsigned int ALuint;

#define MAX_AUDIO_BUFFERS 128 // maximum number of sound files loading into memory
#define MAX_AUDIO_SOURCES 16 // maximum number of simultaneously playing sounds

class ALBuffer;
class ALSource;

class ALController
{
public:

	static inline void Initialize(int* argc, char *argv[])
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new ALController(argc, argv);
	}

	static inline ALController* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		ASSERT(s_pkInstance)
		delete s_pkInstance;
	}

	void StopAllSounds(void);

	void Configure(void);
	const bool CheckForAlutError(void) const; 
	const bool CheckForALError(void) const;

	ALSource* GetAvailableSource(void);
	void FreeSource(ALSource* pkSource);

	const inline ALuint GetSource(const ALuint uiIndex) const { return m_pkSources[uiIndex]; }
	const inline ALuint GetBuffer(const ALuint uiIndex) const { return m_pkBuffers[uiIndex]; }

	ALBuffer* LoadSound(const char* sFileName);

private:
	
	ALController(int* argc, char *argv[]);
	~ALController();
	static ALController* s_pkInstance;
	unsigned int m_uiBuffersAvailable;
	ALuint m_pkBuffers[MAX_AUDIO_BUFFERS];
	ALuint m_pkSources[MAX_AUDIO_SOURCES];
	std::vector<ALSource*> m_vpkAvailableSources;
	std::list<ALSource*> m_vpkUsedSources;
};

#endif