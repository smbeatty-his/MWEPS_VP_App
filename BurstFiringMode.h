#ifndef BURST_FIRING_MODE_MODULE_H
#define BURST_FIRING_MODE_MODULE_H

#include <IFiringMode.h>

///////////////////////////////////////////////////////////////////////////////
///
/// @class BurstFiringMode
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class BurstFiringMode : public IFiringMode
{

public:

	BurstFiringMode(void);
	virtual ~BurstFiringMode(void);
	virtual void Fire(void);
	virtual void Update(double dDeltaTime);
	const inline void SetBurstSize(const unsigned int uiSize) { m_uiBurstSize = uiSize; }
	const inline unsigned int GetBurstSize(void) { return m_uiBurstSize; }
	const inline void SetBurstCount(const unsigned int uiCount) { m_uiBurstCount = uiCount; }
	const inline unsigned int GetBurstCount(void) { return m_uiBurstCount; }

private:
	unsigned int m_uiBurstSize;
	unsigned int m_uiBurstCount;
	double m_dShotDelayRate;
	double m_dShotDelayAccumTime;
	bool m_bFiring;
};

#endif