//----------------------------------------------------------------------------
/// @file SeekBehavior.h
/// This file contains the declaration of the SeekBehavior class
//----------------------------------------------------------------------------

#ifndef SEEK_BEHAVIOR_MODULE_H
#define SEEK_BEHAVIOR_MODULE_H

#include <ISteeringBehavior.h>

//-----------------------------------------------------------------------------
/// @class SeekBehavior
///
/// @brief This class will be used to calculate the proper steering force for
///		   a given Target, in regards to moving towards the next node that is
///		   contained in its plotted path
//-----------------------------------------------------------------------------

class SeekBehavior : public ISteeringBehavior
{
	public:
		SeekBehavior();
		virtual ~SeekBehavior();

		virtual const vuVec3<double> Calculate(ITarget* pkTarget);
		inline void SetTargetPoint(const vuVec3<double>& vdTarget) { m_vdTargetPoint = vdTarget; } 

private:

		vuVec3<double> m_vdTargetPoint;

};


#endif