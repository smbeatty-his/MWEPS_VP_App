#include <al.h>
#include <alc.h>
#include <AL\alut.h>
#include <ALController.h>
#include <ALBuffer.h>

ALBuffer::ALBuffer(ALuint uiBuffer)
{
	m_uiBuffer = uiBuffer;
}

ALBuffer::~ALBuffer(void)
{
	
}

void ALBuffer::BufferData(ALenum kFormat, const void *pkData, int iSize, int iFreq)
{
	alBufferData(ALController::GetInstance()->GetBuffer(m_uiBuffer), kFormat, pkData, iSize, iFreq);
}

const ALuint ALBuffer::GetBits(void) const
{
	ALint iBits;
	alGetBufferi(ALController::GetInstance()->GetBuffer(m_uiBuffer), AL_BITS, &iBits);
	return iBits;
}

const ALuint ALBuffer::GetSize(void) const
{
	ALint iSize;
	alGetBufferi(ALController::GetInstance()->GetBuffer(m_uiBuffer), AL_SIZE, &iSize);
	return iSize;
}

const ALuint ALBuffer::GetNumChannels(void) const
{
	ALint iNumChannels;
	alGetBufferi(ALController::GetInstance()->GetBuffer(m_uiBuffer), AL_CHANNELS, &iNumChannels);
	return iNumChannels;
}

const ALuint ALBuffer::GetFrequency(void) const
{
	ALint iFrequency;
	alGetBufferi(ALController::GetInstance()->GetBuffer(m_uiBuffer), AL_CHANNELS, &iFrequency);
	return iFrequency;
}