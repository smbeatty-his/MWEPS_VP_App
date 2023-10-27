//----------------------------------------------------------------------------
/// @file ArriveBehavior.h
/// This file contains the declaration of the ArriveBehavior class
//----------------------------------------------------------------------------

#ifndef ARRIVE_BEHAVIOR_MODULE_H
#define ARRIVE_BEHAVIOR_MODULE_H

#include <ISteeringBehavior.h>

//-----------------------------------------------------------------------------
/// @class ArriveBehavior
///
/// @brief This class will be used to calculate the proper steering force for
///		   a given NPC, in regards to slowing to arrive at a node on its path
///		   where the NPC will exhibit a behavior
//-----------------------------------------------------------------------------

class ArriveBehavior : public ISteeringBehavior
{
	public:
		ArriveBehavior();
		virtual ~ArriveBehavior();

		const virtual vuVec3<double> Calculate(ITarget* pkTarget);

		inline void SetTargetPoint(const vuVec3<double>& vdTarget) { m_vdTargetPoint = vdTarget; } 

	private:

		vuVec3<double> m_vdTargetPoint;
};

#endif