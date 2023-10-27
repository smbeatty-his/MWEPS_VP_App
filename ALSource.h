#ifndef AL_SOURCE_MODULE_H
#define AL_SOURCE_MODULE_H

#include <vector>

typedef unsigned int ALuint;

class ALSource
{
public:

	ALSource(const ALuint uiSource);
	~ALSource(void);
	void Play(void);
	void Pause(void);
	void Stop(void);
	void Rewind(void);
	void QueueBuffers(const int iNumBuffers, ALuint* pkBuffers);
	void UnqueueBuffers(const int iNumBuffers, ALuint* pkBuffers);
	void SetPosition(const float fX, const float fY, const float fZ);
	void SetDirection(const float fH, const float fP, const float fR);
	void SetVelocity(const float fX, const float fY, const float fZ);
	void SetPitch(const float fPitch);
	void SetGain(const float fGain);
	void SetMinGain(const float fMin);
	void SetMaxGain(const float fMax);
	void SetMaxDistance(const float fMaxDist);
	void SetRollOffFactor(const float fRollOff);
	void SetConeOuterGain(const float fOuterGain);
	void SetConeInnerAngle(const float fInnerAngle);
	void SetConeOuterAngle(const float fOuterAngle);
	void SetReferenceDistance(const float fRefDist);
	void SetSourceRelative(const int iSourceRel);
	void SetLooping(const bool bLooping);
	void SetBuffer(const int iBuffer);
	void SetSourceState(const int iState);
	const float GetPitch(void) const;
	const float GetGain(void) const;
	const float GetMinGain(void) const;
	const float GetMaxGain(void) const;
	const float GetMaxDistance(void) const;
	const float GetRollOffFactor(void) const;
	const float GetOuterGain(void) const;
	const float GetConeInnerAngle(void) const;
	const float GetConeOuterAngle(void) const;
	const float GetReferenceDistance(void) const;
	const float GetPositionX(void) const;
	const float GetPositionY(void) const;
	const float GetPositionZ(void) const;
	void GetPosition(float* fX, float* fY, float* fZ) const;
	const float GetVelocityX(void) const;
	const float GetVelocityY(void) const;
	const float GetVelocityZ(void) const;
	void GetVelocity(float* fX, float* fY, float* fZ) const;
	const float GetDirectionH(void) const;
	const float GetDirectionP(void) const;
	const float GetDirectionR(void) const;
	void GetDirection(float* fH, float* fP, float* fR) const;
	const int GetSourceRelative(void) const;
	const bool GetLooping(void) const;
	const int GetBuffer(void) const;
	const int GetSourceState(void) const;
	const int GetBuffersQueued(void) const;
	inline const bool IsReserved(void) const { return m_bIsReserved; }
	inline void SetReserved(const bool bReserved) { m_bIsReserved = bReserved; }

private:

	ALuint m_uiSource;
	bool m_bIsReserved;

};

#endif