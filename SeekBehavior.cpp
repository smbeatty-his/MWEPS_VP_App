//----------------------------------------------------------------------------
/// @file SeekBehavior.cpp
/// This file contains the definitions of the member functions of the
/// SeekBehavior class
//----------------------------------------------------------------------------

#include <SeekBehavior.h>
#include <ITarget.h>
#include <vpPathWayPointSet.h>

//-----------------------------------------------------------------------------
///
/// SeekBehavior::SeekBehavior()
///
/// @brief Default Constructor
///
//-----------------------------------------------------------------------------

SeekBehavior::SeekBehavior()
{
	
}

//-----------------------------------------------------------------------------
///
/// SeekBehavior::~SeekBehavior()
///
/// @brief Destructor
//-----------------------------------------------------------------------------

SeekBehavior::~SeekBehavior()
{

}

//-----------------------------------------------------------------------------
///
/// SeekBehavior::Calculate
///
/// @param pkTarget - Pointer to the Target for which steering force is being
///				   calculated.
///
/// @return vuVec3<double> - Steering force calculated for this behavior 
///
/// @brief Given a Target, this behavior returns a steering force which
/// will direct the Target towards its desired waypoint.
///
//-----------------------------------------------------------------------------
const vuVec3<double> SeekBehavior::Calculate(ITarget* pkTarget)
{
	ASSERT(pkTarget)
	
	vuVec3<double> vdTargetPos;
	pkTarget->GetTargetObject()->getTranslate(&(vdTargetPos[0]), &(vdTargetPos[1]), &(vdTargetPos[2]));

	vuVec3<double> vdDistToTarget = m_vdTargetPoint;

	vdDistToTarget[0] -= vdTargetPos[0];
	vdDistToTarget[1] -= vdTargetPos[1];
	vdDistToTarget[2] = 0.0;

	vdDistToTarget.normalize();

	vuVec3<double> vdDesiredVelocity = vdDistToTarget * pkTarget->GetMaxSpeed();

	return (vdDesiredVelocity + (pkTarget->GetVelocity() * -1));
}