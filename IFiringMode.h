#ifndef FIRING_MODE_MODULE_H
#define FIRING_MODE_MODULE_H

///////////////////////////////////////////////////////////////////////////////
///
/// @class IFiringMode
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class IFiringMode
{

public:

	IFiringMode() { }
	virtual ~IFiringMode() { }
	virtual void Fire(void) = 0;
	virtual void Update(double dDeltaTime) = 0;
	virtual void TriggerReleased(void) { };

private:

};

#endif