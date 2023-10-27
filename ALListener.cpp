#include <al.h>
#include <alc.h>
#include <AL\alut.h>
#include <ALListener.h>


ALListener::ALListener(void) 
{
	SetGain(1.0f);
}

ALListener::~ALListener(void)
{

}

void ALListener::SetGain(const float fGain)
{
	alListenerf(AL_GAIN, fGain);
}

const float ALListener::GetGain(void) const
{
	float fGain;
	alGetListenerf(AL_GAIN, &fGain);
	return fGain;
}

void ALListener::SetPosition(const float fX, const float fY, const float fZ)
{
	alListener3f(AL_POSITION, fX, fY, fZ);
}

const float ALListener::GetPositionX(void) const
{
	float fX, fY, fZ;
	alGetListener3f(AL_POSITION, &fX, &fY, &fZ);
	return fX;
}

const float ALListener::GetPositionY(void) const
{
	float fX, fY, fZ;
	alGetListener3f(AL_POSITION, &fX, &fY, &fZ);
	return fY;
}

const float ALListener::GetPositionZ(void) const
{
	float fX, fY, fZ;
	alGetListener3f(AL_POSITION, &fX, &fY, &fZ);
	return fZ;
}

void ALListener::GetPosition(float* fX, float* fY, float* fZ) const
{
	alGetListener3f(AL_POSITION, fX, fY, fZ);
}

void ALListener::SetVelocity(const float fX, const float fY, const float fZ)
{
	alListener3f(AL_VELOCITY, fX, fY, fZ);
}

const float ALListener::GetVelocityX(void) const
{
	float fX, fY, fZ;
	alGetListener3f(AL_VELOCITY, &fX, &fY, &fZ);
	return fX;
}

const float ALListener::GetVelocityY(void) const
{
	float fX, fY, fZ;
	alGetListener3f(AL_VELOCITY, &fX, &fY, &fZ);
	return fY;
}

const float ALListener::GetVelocityZ(void) const
{
	float fX, fY, fZ;
	alGetListener3f(AL_VELOCITY, &fX, &fY, &fZ);
	return fZ;
}

void ALListener::GetVelocity(float *fX, float *fY, float *fZ) const
{
	alGetListener3f(AL_VELOCITY, fX, fY, fZ);
}

void ALListener::GetOrientation(float* fOrient)
{
	alGetListenerfv(AL_ORIENTATION, fOrient);
}

void ALListener::SetOrientation(float* fOrient)
{
	alListenerfv(AL_ORIENTATION, fOrient);
}