#ifndef AL_BUFFER_MODULE_H
#define AL_BUFFER_MODULE_H

typedef int ALenum;
typedef unsigned int ALuint;

class ALBuffer
{
public:

	ALBuffer(const ALuint uiBuffer);
	~ALBuffer(void);
	void BufferData(ALenum kFormat, const void* pkData, int iSize, int iFreq);
	const inline ALuint GetBuffer(void) const { return m_uiBuffer; }
	const ALuint GetSize(void) const;
	const ALuint GetBits(void) const;
	const ALuint GetNumChannels(void) const;
	const ALuint GetFrequency(void) const;
	
private:

	ALuint m_uiBuffer;

};

#endif