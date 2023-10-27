#ifndef PICKER_MODULE_H
#define PICKER_MODULE_H

// create a simple picker class to perform intersection tests w/ the scene
// graph for a given mouse position
#include <vuField.h>
#include <vuClassType.h>
#include <vsNode.h>
#include <vpIsectorLOS.h>

class vpScene;
class vpChannel;

///////////////////////////////////////////////////////////////////////////////
///
/// @class Picker
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class Picker 
{

public:

    Picker(vpScene *scene, uint mask = 0xFFFFFFFF);
	~Picker();

    // picking modes to select either objects or nodes
    enum Mode 
	{
        MODE_OBJECT,   // select all geometry under the closest parent of the 
                       // picked geometry that is an object
        MODE_GEOMETRY, // select only the picked geometry.  Note that this may
                       // be in a different LOD than the one you're seeing.
        MODE_DOF,      // select all geometry under the closest parent of the 
                       // picked geometry that is a dof
        MODE_LOD       // select all geometry under the closest parent of the 
                       // picked geometry that is a lod
    };

    /**
     * set / get the picking mode
     */
    inline void setMode(const Mode mode) { m_mode = mode; }

    const inline Mode getMode() const { return m_mode; }

    /**
     * intersect w/ the scene at the given mouse position
     */
    vsNode* Pick(vpChannel* pkChannel, const float fMX, const float fMY);

	vuVec3<double>* MouseCoordsToMouseRotationVector(vpChannel* pkChannel, const float fMX, const float fMY);

	inline vuField<vpIsectorLOS*>* GetISectorResult(void) { return &m_isector; };

private:

    //Walk up the parents till a vsDOF node is found
    vsNode* GetParent(vsNode* child, vuClassType* classType)
	{
		if (child != NULL) 
		{
			vsNode::const_iterator_parent it, ite = child->end_parent();

			for(it = child->begin_parent(); it != ite ; ++it) 
			{
				if((*it)->isOfClassType(classType))
				{
					return *it;
				}   
				else 
				{
					return GetParent(*it, classType);
				}
			}
		}
	
		return NULL;
	}

    // select either picking of objects or nodes
    Mode m_mode;
    // an isector for use w/ intersection tests
    vuField<vpIsectorLOS*> m_isector;
};

#endif