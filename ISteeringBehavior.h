#ifndef ISTEERING_BEHAVIOR_MODULE_H
#define ISTEERING_BEHAVIOR_MODULE_H

#include <DebugUtil.h>
#include <vuVec3.h>

class ITarget;

class ISteeringBehavior
{

public:

	virtual ~ISteeringBehavior(void) {};

	virtual const vuVec3<double> Calculate(ITarget* pkTarget) = 0;

	const inline double GetWeight(void) const { return m_dWeight; }
	const inline void SetWeight(const double dWeight) { m_dWeight = dWeight; }

protected:

	ISteeringBehavior(void) {};

private:
	
	double m_dWeight;
	
};

#endif