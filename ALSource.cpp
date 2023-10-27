#include <al.h>
#include <alc.h>
#include <AL\alut.h>
#include <ALSource.h>
#include <ALController.h>
#include <DebugUtil.h>

ALSource::ALSource(ALuint uiSource)
{
	m_uiSource = uiSource;
}

ALSource::~ALSource(void)
{
	
}

void ALSource::Play(void)
{
	alSourcePlay(m_uiSource);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::Pause(void)
{
	alSourcePause(m_uiSource);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::Stop(void)
{
	alSourceStop(m_uiSource);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::Rewind(void)
{
	alSourceRewind(m_uiSource);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::QueueBuffers(const int iNumBuffers, ALuint* pkBuffers)
{
	alSourceQueueBuffers(m_uiSource, iNumBuffers, pkBuffers);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::UnqueueBuffers(const int iNumBuffers, ALuint* pkBuffers)
{
	alSourceUnqueueBuffers(m_uiSource, iNumBuffers, pkBuffers);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetPosition(const float fX, const float fY, const float fZ)
{
	alSource3f(m_uiSource, AL_POSITION, fX, fY, fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetDirection(const float fH, const float fP, const float fR)
{
	alSource3f(m_uiSource, AL_DIRECTION, fH, fP, fR);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetVelocity(const float fX, const float fY, const float fZ)
{
	alSource3f(m_uiSource, AL_VELOCITY, fX, fY, fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetPitch(const float fPitch)
{
	alSourcef(m_uiSource, AL_PITCH, fPitch);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetGain(const float fGain)
{
	alSourcef(m_uiSource, AL_GAIN, fGain);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetMinGain(const float fMin)
{	
	alSourcef(m_uiSource, AL_MIN_GAIN, fMin);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetMaxGain(const float fMax)
{	
	alSourcef(m_uiSource, AL_MAX_GAIN, fMax);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetMaxDistance(const float fMaxDist)
{
	alSourcef(m_uiSource, AL_MAX_DISTANCE, fMaxDist);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetRollOffFactor(const float fRollOff)
{
	alSourcef(m_uiSource, AL_ROLLOFF_FACTOR, fRollOff);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetConeOuterGain(const float fOuterGain)
{
	alSourcef(m_uiSource, AL_CONE_OUTER_GAIN, fOuterGain);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetConeInnerAngle(const float fInnerAngle)
{
	alSourcef(m_uiSource, AL_CONE_INNER_ANGLE, fInnerAngle);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetConeOuterAngle(const float fOuterAngle)
{
	alSourcef(m_uiSource, AL_CONE_OUTER_ANGLE, fOuterAngle);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetReferenceDistance(const float fRefDist)
{
	alSourcef(m_uiSource, AL_REFERENCE_DISTANCE, fRefDist);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetSourceRelative(const int iSourceRel)
{
	alSourcei(m_uiSource, AL_SOURCE_RELATIVE, iSourceRel);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetLooping(const bool bLooping)
{
	alSourcei(m_uiSource, AL_LOOPING, bLooping);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetBuffer(const int iBuffer)
{
	alSourcei(m_uiSource, AL_BUFFER, iBuffer);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

void ALSource::SetSourceState(const int iState)
{
	alSourcei(m_uiSource, AL_SOURCE_STATE, iState);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

const float ALSource::GetPitch(void) const
{
	float fPitch;
	alGetSourcef(m_uiSource, AL_PITCH, &fPitch);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fPitch;
}

const float ALSource::GetGain(void) const
{
	float fGain;
	alGetSourcef(m_uiSource, AL_GAIN, &fGain);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fGain;
}

const float ALSource::GetMinGain(void) const
{
	float fMin;
	alGetSourcef(m_uiSource, AL_MIN_GAIN, &fMin);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fMin;
}

const float ALSource::GetMaxGain(void) const
{
	float fMax;
	alGetSourcef(m_uiSource, AL_MAX_GAIN, &fMax);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fMax;
}

const float ALSource::GetMaxDistance(void) const
{
	float fMax;
	alGetSourcef(m_uiSource, AL_MAX_DISTANCE, &fMax);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fMax;
}

const float ALSource::GetRollOffFactor(void) const
{
	float fRollOff;
	alGetSourcef(m_uiSource, AL_ROLLOFF_FACTOR, &fRollOff);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fRollOff;
}

const float ALSource::GetOuterGain(void) const
{
	float fOuterGain;
	alGetSourcef(m_uiSource, AL_CONE_OUTER_GAIN, &fOuterGain);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fOuterGain;
}

const float ALSource::GetConeInnerAngle(void) const
{
	float fInnerAngle;
	alGetSourcef(m_uiSource, AL_CONE_INNER_ANGLE, &fInnerAngle);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fInnerAngle;
}

const float ALSource::GetConeOuterAngle(void) const
{
	float fOuterAngle;
	alGetSourcef(m_uiSource, AL_CONE_OUTER_ANGLE, &fOuterAngle);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fOuterAngle;
}

const float ALSource::GetReferenceDistance(void) const
{
	float fRefDist;
	alGetSourcef(m_uiSource, AL_REFERENCE_DISTANCE, &fRefDist);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fRefDist;
}

const float ALSource::GetPositionX(void) const
{
	float fX, fY, fZ;
	alGetSource3f(m_uiSource, AL_POSITION, &fX, &fY, &fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fX;
}

const float ALSource::GetPositionY(void) const
{
	float fX, fY, fZ;
	alGetSource3f(m_uiSource, AL_POSITION, &fX, &fY, &fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fY;
}

const float ALSource::GetPositionZ(void) const
{
	float fX, fY, fZ;
	alGetSource3f(m_uiSource, AL_POSITION, &fX, &fY, &fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fZ;
}

void ALSource::GetPosition(float* fX, float* fY, float* fZ) const
{
	alGetSource3f(m_uiSource, AL_POSITION, fX, fY, fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

const float ALSource::GetVelocityX(void) const
{
	float fX, fY, fZ;
	alGetSource3f(m_uiSource, AL_VELOCITY, &fX, &fY, &fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fX;
}

const float ALSource::GetVelocityY(void) const
{
	float fX, fY, fZ;
	alGetSource3f(m_uiSource, AL_VELOCITY, &fX, &fY, &fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fY;
}

const float ALSource::GetVelocityZ(void) const
{
	float fX, fY, fZ;
	alGetSource3f(m_uiSource, AL_VELOCITY, &fX, &fY, &fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fZ;
}

void ALSource::GetVelocity(float* fX, float* fY, float* fZ) const
{
	alGetSource3f(m_uiSource, AL_VELOCITY, fX, fY, fZ);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

const float ALSource::GetDirectionH(void) const
{
	float fH, fP, fR;
	alGetSource3f(m_uiSource, AL_DIRECTION, &fH, &fP, &fR);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fH;
}

const float ALSource::GetDirectionP(void) const
{
	float fH, fP, fR;
	alGetSource3f(m_uiSource, AL_DIRECTION, &fH, &fP, &fR);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fP;
}

const float ALSource::GetDirectionR(void) const
{
	float fH, fP, fR;
	alGetSource3f(m_uiSource, AL_DIRECTION, &fH, &fP, &fR);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return fR;
}

void ALSource::GetDirection(float* fH, float* fP, float* fR) const
{
	alGetSource3f(m_uiSource, AL_DIRECTION, fH, fP, fR);
	ASSERT(! ALController::GetInstance()->CheckForALError())
}

const int ALSource::GetSourceRelative(void) const
{
	int iSourceRel;
	alGetSourcei(m_uiSource, AL_SOURCE_RELATIVE, &iSourceRel);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return iSourceRel;
}

const int ALSource::GetSourceState(void) const
{
	int iSourceState;
	alGetSourcei(m_uiSource, AL_SOURCE_STATE, &iSourceState);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return iSourceState;
}

const bool ALSource::GetLooping(void) const
{
	int iLooping;
	alGetSourcei(m_uiSource, AL_LOOPING, &iLooping);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return (iLooping != 0);
}

const int ALSource::GetBuffersQueued(void) const
{
	int iBuffersQueued;
	alGetSourcei(m_uiSource, AL_BUFFERS_QUEUED, &iBuffersQueued);
	ASSERT(! ALController::GetInstance()->CheckForALError())
	return iBuffersQueued;
}
