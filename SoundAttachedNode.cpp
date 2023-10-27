#include <SoundAttachedNode.h>
#include <vpObject.h>

SoundAttachedNode::SoundAttachedNode(bool bReleases) : SoundNode(bReleases)
{

}

SoundAttachedNode::~SoundAttachedNode(void)
{
	
}

void SoundAttachedNode::ConfigureSource(void)
{
	SoundNode::ConfigureSource();
}

void SoundAttachedNode::ProcessData(const vuMap<CharPointer,const char*>& msTagMap)
{
	if (msTagMap.count("StartState"))
	{
		SetStartState(atoi(msTagMap.find("StartState")->second));
	}

	if (msTagMap.count("EndState"))
	{
		SetEndState(atoi(msTagMap.find("EndState")->second));
	}

	SoundNode::ProcessData(msTagMap);
}

void SoundAttachedNode::CloneSound(SoundAttachedNode *pkSound)
{
	vsgu::copy<SoundAttachedNode>(this, pkSound);
}

void SoundAttachedNode::Update(vpObject* pkObject)
{

}

void SoundAttachedNode::Activate(vpObject* pkObject)
{
	ConfigureSource();
	Play();
}