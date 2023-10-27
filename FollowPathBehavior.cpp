 //----------------------------------------------------------------------------
/// @file FollowPathBehavior.cpp
/// This file contains the definitions of the member functions of the
/// FollowPathBehavior class
//----------------------------------------------------------------------------

#include <FollowPathBehavior.h>
#include <ITarget.h>
#include <DebugUtil.h>
#include <vuVec3.h>
#include <vpPathWayPointSet.h>

#define ARRIVAL_TOLERANCE_ADJUSTMENT 30
#define NO_BEHAVIOR_SET -1

//-----------------------------------------------------------------------------
/// FollowPathBehavior::FollowPathBehavior
///
/// @brief Default Constructor
//-----------------------------------------------------------------------------

FollowPathBehavior::FollowPathBehavior()
{
	//Initialization for behavior weights for Seek and Arrive sub-behaviors
	m_kSeekBehavior.SetWeight(1.0f);
	m_kArriveBehavior.SetWeight(1.0f);
}

//-----------------------------------------------------------------------------
/// FollowPathBehavior::~FollowPathBehavior 
///
/// @brief Destructor
//-----------------------------------------------------------------------------
FollowPathBehavior::~FollowPathBehavior()
{

}
//-----------------------------------------------------------------------------
/// FollowPathBehavior::Calculate
///
/// @param pkTarget - Pointer to the Target for which steering force is being
///				   calculated.
///
/// @return vuVec3<double> - Steering force calculated for this behavior
///
///	@brief Given a series of Path Nodes, this method produces a force that will 
/// move the Target along the nodes in order. The Target uses the Seek behavior 
/// to move to the next node - unless it is supposed to stop at that node,
/// in which case it Arrives.
//-----------------------------------------------------------------------------

const vuVec3<double> FollowPathBehavior::Calculate(ITarget* pkTarget)
{
	ASSERT(pkTarget)

	//If NPC has no path list assigned to it
	if (! pkTarget->GetActiveWayPointSet())
	{
		///Have no path to follow, so return a force of zero
		return vuVec3<double>(0.0, 0.0, 0.0);
	}

	//Calculate X and Y components of distance to node in path list NPC is 
	//currently trying to reach.
	
	vuVec3<double> vdWayPointPos;  
	pkTarget->GetActiveWayPointSet()->getWayPoint(pkTarget->GetWayPointIndex())->getPosition(&vdWayPointPos);

	float fXVal = vdWayPointPos[0] - pkTarget->GetTargetObject()->getTranslateX();
	float fYVal = vdWayPointPos[1] - pkTarget->GetTargetObject()->getTranslateY();

	//If Target is not within tolerance for reaching node
	if ((fXVal * fXVal + fYVal * fYVal) > 
		(ARRIVAL_TOLERANCE_ADJUSTMENT * pkTarget->GetMaxSpeed()))
	{
		m_kSeekBehavior.SetTargetPoint(vdWayPointPos);

		//Calculate steering force directing NPC towards current node on 
		//its path  
		return m_kSeekBehavior.Calculate(pkTarget);
	}
	
	else if (pkTarget->GetWayPointIndex() < (pkTarget->GetActiveWayPointSet()->getNumWayPoints() - 1))
	{
		pkTarget->SetWayPointIndex(pkTarget->GetWayPointIndex() + 1);

		pkTarget->GetActiveWayPointSet()->getWayPoint(pkTarget->GetWayPointIndex())->getPosition(&vdWayPointPos);

		m_kSeekBehavior.SetTargetPoint(vdWayPointPos);

		return m_kSeekBehavior.Calculate(pkTarget);
	}

	else
	{
		m_kArriveBehavior.SetTargetPoint(vdWayPointPos);

		return m_kArriveBehavior.Calculate(pkTarget);
	}
}