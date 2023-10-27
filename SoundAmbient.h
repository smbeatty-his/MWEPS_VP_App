#ifndef SOUND_AMBIENT_MODULE_H
#define SOUND_AMBIENT_MODULE_H

#include <ISound.h>
#include <vuBase.h>
#include <Factory.h>

class SoundAmbient : public ISound
{
public:

	
	~SoundAmbient(void);
	virtual void ConfigureSource(void);
	virtual void PopulateAttachedSound(SoundAttachedNode* pkSound);
	void Copy(SoundAmbient* pkSound);

	ConcreteFactory(ISound, SoundAmbient);

private:
	
	SoundAmbient(bool bRelease = true);

};

typedef SoundAmbient::SoundAmbientFactory SoundAmbientFactory;

#endif