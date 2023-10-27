#ifndef SINGLE_SHOT_FIRING_MODE_MODULE_H
#define SINGLE_SHOT_FIRING_MODE_MODULE_H

#include <IFiringMode.h>

///////////////////////////////////////////////////////////////////////////////
///
/// @class SingleShotFiringMode
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class SingleShotFiringMode : public IFiringMode
{

public:

	SingleShotFiringMode(void) {};
	virtual ~SingleShotFiringMode(void) {};
	virtual void Fire(void);
	virtual void Update(double dDeltaTime);

private:


};

#endif