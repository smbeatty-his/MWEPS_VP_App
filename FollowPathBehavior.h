//----------------------------------------------------------------------------
/// @file FollowPathBehavior.h
/// This file contains the declaration of the FollowPathBehavior class
//----------------------------------------------------------------------------

#ifndef FOLLOW_PATH_BEHAVIOR_MODULE_H
#define FOLLOW_PATH_BEHAVIOR_MODULE_H

#include <ISteeringBehavior.h>
#include <SeekBehavior.h>
#include <ArriveBehavior.h>
#include <Factory.h>

//-----------------------------------------------------------------------------
/// @class FollowPathBehavior
///
/// @brief This class will be used to calculate the proper steering force for
///		   a given Target, in regards to following its set path through the
///		   environment.  Depending on whether or not the Target is arriving at  
///		   a node where it will stop will determine if the Seek behavior or
///		   the Arrive behavior is used for this calculation on a given frame		   
///		   
//-----------------------------------------------------------------------------

class FollowPathBehavior : public ISteeringBehavior
{
	public:
		virtual ~FollowPathBehavior(void);
		virtual const vuVec3<double> Calculate(ITarget* pkTarget);

		ConcreteFactory(ISteeringBehavior, FollowPathBehavior)

	private:
		FollowPathBehavior(void);

		SeekBehavior m_kSeekBehavior;
		ArriveBehavior m_kArriveBehavior;
};

typedef FollowPathBehavior::FollowPathBehaviorFactory FollowPathBehaviorFactory;

#endif