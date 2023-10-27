#ifndef SOUND_MANAGER_MODULE_H
#define SOUND_MANAGER_MODULE_H

#include <DebugUtil.h>
#include <vuMap.h>
#include <vuVec3.h>
#include <vuList.h>
#include <CharPointer.h>

class AudioListener;
class ALSource;
class ISound;
class SoundAttachedNode;

class SoundManager
{
public:

	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new SoundManager();
	}

	static inline SoundManager* GetInstance(void) 
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		delete s_pkInstance;
	}

	void PlayEnviromentalSound(CharPointer sSound, const vuVec3<double>& vdPos);
	void PlayAmbientSound(CharPointer sSound);
	SoundAttachedNode* SpawnAttachedSound(CharPointer sSound, const char* sClassType);

	const inline void AddSound(ISound* pkSound, CharPointer sSoundName) 
	{
		ASSERT(pkSound)
		m_mpkAvailableSounds.insert(std::pair<CharPointer, ISound*>(sSoundName, pkSound));
	}
	void ClearSoundFromSource(ALSource* pkSource);
	void Update(void);
	void Reset(void);
	void Start(void);
	const bool CheckForALError(void) const;

private:
	SoundManager();
	~SoundManager();
	AudioListener* m_pkListener;
	vuMap<CharPointer, ISound*> m_mpkAvailableSounds;
	vuList<ISound*> m_vpkPlayingSounds;
	static SoundManager* s_pkInstance;
};

#endif