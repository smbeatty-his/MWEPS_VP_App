#ifndef AUTO_FIRING_MODE_MODULE_H
#define AUTO_FIRING_MODE_MODULE_H

#include <IFiringMode.h>

///////////////////////////////////////////////////////////////////////////////
///
/// @class AutoFiringMode
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class AutoFiringMode : public IFiringMode
{

public:

	AutoFiringMode(void);
	virtual ~AutoFiringMode(void);
	virtual void Fire(void);
	virtual void Update(double dDeltaTime);
	virtual void TriggerReleased(void);


private:

	bool m_bFiring;
	double m_dShotDelayRate;
	double m_dShotDelayAccumTime;
};

#endif