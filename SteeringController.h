#ifndef STEERING_CONTROLLER_MODULE_H
#define STEERING_CONTROLLER_MODULE_H

#include <DebugUtil.h>
#include <vuVector.h>
#include <vuVec3.h>

class ITarget;
class ISteeringBehavior;

class SteeringController
{
public:

	SteeringController(void);
	~SteeringController(void);
	const vuVec3<double>& Calculate(ITarget* pkTarget);
	const inline void AddSteeringBehavior(ISteeringBehavior* pkBehavior)
	{
		ASSERT(pkBehavior)
		m_vpkSteeringBehaviors.push_back(pkBehavior);
	}

private:

	const bool AccumulateForce(ITarget* pkTarget, vuVec3<double>& vdForce);
	double m_dAvailableAcceleration;
	vuVec3<double> m_vdAcceleration;
	vuVector<ISteeringBehavior*> m_vpkSteeringBehaviors;
	
};

#endif