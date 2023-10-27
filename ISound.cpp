#include <ISound.h>
#include <vuMap.h>

ISound::ISound(bool bReleases) : ALSound(bReleases)
{

}

ISound::~ISound(void)
{

}

void ISound::ParseData(tinyxml2::XMLNode* pkNode)
{
	vuMap<CharPointer, const char*> msTagMap;

	while (pkNode)
	{
		ASSERT(pkNode->FirstChild())
		ASSERT(pkNode->Value())
		ASSERT(pkNode->FirstChild()->Value())

		msTagMap.insert(std::pair<CharPointer, const char*>(pkNode->Value(), pkNode->FirstChild()->Value()));
		
		pkNode = pkNode->NextSibling();
	}

	ProcessData(msTagMap);
}

void ISound::ProcessData(const vuMap<CharPointer,const char*>& msTagMap)
{
	if (msTagMap.count("Gain"))
	{
		SetGain((float) atof(msTagMap.find("Gain")->second));
	}

	if (msTagMap.count("Pitch"))
	{
		SetPitch((float) atof(msTagMap.find("Pitch")->second));
	}

	if (msTagMap.count("MaxGain"))
	{
		SetMaxGain((float) atof(msTagMap.find("MaxGain")->second));
	}

	if (msTagMap.count("MinGain"))
	{
		SetMinGain((float) atof(msTagMap.find("MinGain")->second));
	}

	if (msTagMap.count("Looping"))
	{
		SetLooping(atoi(msTagMap.find("Looping")->second) != 0);
	}

	if (msTagMap.count("ReleaseOnCompletion"))
	{
		SetReleaseOnCompletion(atoi(msTagMap.find("ReleaseOnCompletion")->second) != 0);
	}
}
