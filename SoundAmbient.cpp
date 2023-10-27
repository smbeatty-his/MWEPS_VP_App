#include <al.h>
#include <ALSource.h>
#include <SoundAmbient.h>
#include <tinyxml2.h>
#include <SoundAttachedNode.h>


SoundAmbient::SoundAmbient(bool bRelease) : ISound(bRelease)
{
	
}

SoundAmbient::~SoundAmbient(void)
{

}

void SoundAmbient::ConfigureSource(void)
{
	GetSource()->SetSourceRelative(AL_TRUE);
	GetSource()->SetPosition(0.0f, 0.0f, 0.0f);
	ALSound::ConfigureSource();
}

void SoundAmbient::PopulateAttachedSound(SoundAttachedNode* pkSound)
{
	pkSound->SetLooping(GetLooping());
	pkSound->SetGain(GetGain());
	pkSound->SetPitch(GetPitch());
	pkSound->SetMaxGain(GetMaxGain());
	pkSound->SetMinGain(GetMinGain());
	pkSound->SetBuffer(GetBuffer());
	pkSound->SetSource(GetSource());
}

void SoundAmbient::Copy(SoundAmbient* pkSound)
{
	SetLooping(pkSound->GetLooping());
	SetGain(pkSound->GetGain());
	SetPitch(pkSound->GetPitch());
	SetMaxGain(pkSound->GetMaxGain());
	SetMinGain(pkSound->GetMinGain());
	SetBuffer(pkSound->GetBuffer());
	SetSource(pkSound->GetSource());
}