#ifndef ISOUND_MODULE_H
#define ISOUND_MODULE_H

#include <ALSound.h>
#include <Factory.h>
#include <vuMap.h>
#include <CharPointer.h>
#include <tinyxml2.h>

namespace tinyxml2 {
	class XMLNode;
}
class SoundAttachedNode;

class ISound : public ALSound
{
public:

	
	~ISound();
	void ParseData(tinyxml2::XMLNode* pkNode);
	virtual void ProcessData(const vuMap<CharPointer, const char*>& msTagMap); 
	virtual void PopulateAttachedSound(SoundAttachedNode* pkSound) = 0;

protected:

	ISound(bool bReleases = true);

private:
	
};

#endif