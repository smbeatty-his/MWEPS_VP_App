#ifndef AL_SOUND_SPATIAL_MODULE_H
#define AL_SOUND_SPATIAL_MODULE_H

#include <ALSound.h>

class ALSoundSpatial : public ALSound
{
public:

	ALSoundSpatial(bool bRelease = true);
	virtual ~ALSoundSpatial(void);
	inline void SetMaxDistance(const float fMaxDist) { m_fMaxDist = fMaxDist; }
	inline void SetRollOffFactor(const float fRollOff) { m_fRollOffFactor = fRollOff; }
	inline void SetConeOuterGain(const float fOuterGain) { m_fConeOuterGain = fOuterGain; }
	inline void SetConeInnerAngle(const float fInnerAngle) { m_fConeInnerAngle = fInnerAngle; }
	inline void SetConeOuterAngle(const float fOuterAngle) { m_fConeOuterAngle = fOuterAngle; }
	inline void SetReferenceDistance(const float fRefDist) { m_fRefDistance = fRefDist; }
	const inline float GetMaxDistance(void) const { return m_fMaxDist; }
	const inline float GetRollOffFactor(void) const { return m_fRollOffFactor; }
	const inline float GetOuterGain(void) const { return m_fConeOuterGain; }
	const inline float GetConeInnerAngle(void) const { return m_fConeInnerAngle; }
	const inline float GetConeOuterAngle(void) const { return m_fConeOuterAngle; }
	const inline float GetReferenceDistance(void) const { return m_fRefDistance; }

private:

	float m_fMaxDist;
	float m_fRollOffFactor;
	float m_fConeOuterGain;
	float m_fConeInnerAngle;
	float m_fConeOuterAngle;
	float m_fRefDistance;
};

#endif