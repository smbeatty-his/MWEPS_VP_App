#ifndef AL_SOUND_MODULE_H
#define AL_SOUND_MODULE_H

class ALBuffer;
class ALSource;

class ALSound
{

public:
	ALSound(bool bRelease = true);
	virtual ~ALSound(void);
	void LoadSound(const char* sFilename);
	virtual void Play(void);
	virtual void ConfigureSource(void);

	inline ALBuffer* GetBuffer(void) const { return m_pkBuffer; }
	inline ALSource* GetSource(void) const { return m_pkSource; }
	inline void SetBuffer(ALBuffer* pkBuffer) { m_pkBuffer = pkBuffer; }
	inline void SetSource(ALSource* pkSource) { m_pkSource = pkSource; }
	const bool IsPlaying(void) const;
	inline void SetPitch(const float fPitch) { m_fPitch = fPitch; }
	inline void SetGain(const float fGain) { m_fGain = fGain; } 
	inline void SetMinGain(const float fMin) { m_fMinGain = fMin; }
	inline void SetMaxGain(const float fMax) { m_fMaxGain = fMax; }
	inline void SetLooping(const bool bLooping) { m_bLooping = bLooping; }
	const inline float GetPitch(void) const { return m_fPitch; }
	const inline float GetGain(void) const { return m_fGain; }
	const inline float GetMinGain(void) const { return m_fMinGain; }
	const inline float GetMaxGain(void) const { return m_fMaxGain; }
	const inline bool GetLooping(void) const { return m_bLooping; }
	const inline bool ReleaseOnCompletion(void) const { return m_bRelease; }
	const inline void SetReleaseOnCompletion(const bool bRelease) { m_bRelease = bRelease; }

private:
	
	ALBuffer* m_pkBuffer;
	ALSource* m_pkSource;
	bool m_bRelease;
	bool m_bLooping;
	float m_fPitch;
	float m_fGain;
	float m_fMinGain;
	float m_fMaxGain;
	
};

#endif