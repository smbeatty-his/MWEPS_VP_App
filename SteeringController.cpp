#include <SteeringController.h>
#include <ISteeringBehavior.h>
#include <ITarget.h>
#include <vpPathWayPointSet.h>
#include <FollowPathBehavior.h>

SteeringController::SteeringController(void)
{

}

SteeringController::~SteeringController(void)
{

}

const vuVec3<double>& SteeringController::Calculate(ITarget* pkTarget)
{
	m_vdAcceleration = vuVec3<double>(0.0, 0.0, 0.0);

	vuVector<ISteeringBehavior*>::iterator kIter = m_vpkSteeringBehaviors.begin();

	vuVec3<double> vdCurrForce;

	bool bAvailableForce = true;

	for (kIter; kIter != m_vpkSteeringBehaviors.end(); ++kIter)
	{
		if (bAvailableForce)
		{
			vdCurrForce = (*kIter)->Calculate(pkTarget) * (*kIter)->GetWeight();
			bAvailableForce = AccumulateForce(pkTarget, vdCurrForce);
		}
	}

	return m_vdAcceleration;
}

const bool SteeringController::AccumulateForce(ITarget* pkTarget, vuVec3<double>& vdForce)
{
	//calculate how much steering force the vehicle has used so far
	double dMagnitude = m_vdAcceleration[0] * m_vdAcceleration[0] + m_vdAcceleration[1] * m_vdAcceleration[1]
								+ m_vdAcceleration[2] * m_vdAcceleration[2];

	//calculate how much steering force remains to be used by this vehicle
	double dMagRemaining = pkTarget->GetMaxForce() - dMagnitude;

	//return false if there is no more force left to use
	if (dMagRemaining <= 0.0) 
	{
		return false;
	}

	//calculate the magnitude of the force we want to add
	double dMagnitudeNew = vdForce[0] * vdForce[0] + vdForce[1] * vdForce[1] + vdForce[2] * vdForce[2];

	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (dMagnitudeNew < dMagRemaining)
	{
		m_vdAcceleration += vdForce;
	}

	else
	{
        //add it to the steering force
		vdForce.normalize();
        m_vdAcceleration += (vdForce * dMagRemaining); 

		return false;
	}

	return true;
}