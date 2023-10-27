#ifndef LISTENER_MODULE_H
#define LISTENER_MODULE_H

#include <ALListener.h>
#include <vuVec3.h>

///////////////////////////////////////////////////////////////////////////////
///
/// @class AudioListener
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class AudioListener : public ALListener
{
public:
	AudioListener(void);
	virtual ~AudioListener(void);
	const inline vuVec3<double>& GetListenerPosition(void) { return m_vdPosition; }
	void SetListenerPosition(const vuVec3<double>& vdPos);
	void Update(void);

private:
	
	bool m_bAttachedToObserver;
	vuVec3<double> m_vdPosition;
	
};

#endif