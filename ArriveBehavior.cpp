//----------------------------------------------------------------------------
/// @file ArriveBehavior.cpp
/// This file contains the definitions of the member functions of the
/// ArriveBehavior class
//----------------------------------------------------------------------------

#include <ArriveBehavior.h>
#include <ITarget.h>
#include <vpPathWayPointSet.h>


#define NODE_DISTANCE_TOLERANCE 2500.0

//-----------------------------------------------------------------------------
/// ArriveBehavior::ArriveBehavior()
///
/// @brief Default Constructor
//-----------------------------------------------------------------------------
ArriveBehavior::ArriveBehavior()
{
	
}

//-----------------------------------------------------------------------------
/// ArriveBehavior::~ArriveBehavior()
///
/// @brief Destructor
//-----------------------------------------------------------------------------
ArriveBehavior::~ArriveBehavior()
{

}

//-----------------------------------------------------------------------------
/// ArriveBehavior::Calculate
///
/// @param pkTarget Pointer to the Target for which steering force is being
///				 calculated.
///
/// @return vuVec3<double>& - Steering force calculated for this behavior
///
/// @brief Arrive - This behavior is similar to seek but it attempts to arrive
///	at the target with a zero velocity
///
//-----------------------------------------------------------------------------

const vuVec3<double> ArriveBehavior::Calculate(ITarget* pkTarget)
{
	ASSERT(pkTarget)

	//Calculate directional vector from Target to current Way Point it is trying 
	//to reach

	vuVec3<double> vdDistToTarget = m_vdTargetPoint;

	vdDistToTarget[0] -= pkTarget->GetTargetObject()->getTranslateX();
	vdDistToTarget[1] -= pkTarget->GetTargetObject()->getTranslateY();
	vdDistToTarget[2] = 0.0;

	//Calculate distance from Target to current WayPoint it is trying to reach
	double dDist = vdDistToTarget[0] * vdDistToTarget[0] + vdDistToTarget[1] * vdDistToTarget[1];

	//If Target is not within tolerance to reach node
	if (dDist > NODE_DISTANCE_TOLERANCE)
	{
		float dSpeed = dDist * pkTarget->GetDecelerationRate();

		if (dSpeed > pkTarget->GetMaxSpeed())
		{
			dSpeed = pkTarget->GetMaxSpeed();
		}
		
		vuVec3<double> vdDesiredVelocity = vdDistToTarget * (dSpeed / dDist);

		return (vdDesiredVelocity + (-1 * pkTarget->GetVelocity()));
	}

	//Else if Target is close enough to node
	else
	{	
		return (-1 * pkTarget->GetVelocity());	
	}
	
}