#include <AudioListener.h>
#include <vpObserver.h>

AudioListener::AudioListener(void)
{

}

AudioListener::~AudioListener(void)
{

}

void AudioListener::SetListenerPosition(const vuVec3<double>& vdPos)
{
	m_vdPosition = vdPos;
	SetPosition((float) vdPos[0], (float) vdPos[1], (float) vdPos[2]);
}

void AudioListener::Update(void)
{
	if (m_bAttachedToObserver)
	{
		vuVec3<double> vdPos;
		(*vpObserver::begin())->getPosition(&(vdPos[0]), &(vdPos[1]), &(vdPos[2]));
		SetListenerPosition(vdPos);
	}
}