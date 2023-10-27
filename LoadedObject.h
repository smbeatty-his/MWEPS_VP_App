#ifndef LOADED_OBJECT_MODULE_H
#define LOADED_OBJECT_MODULE_H

#include <vpObject.h>

class vsNode;

/*=============================================================================
	MyObject
  ..............................................................................
	This class shows how to manually construct a vpObject and how to remove 
	and replace a node in the scene graph. This assumes that the object is 
	created in the APP thread. 
==============================================================================*/

///////////////////////////////////////////////////////////////////////////////
///
/// @class LoadedObject
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class LoadedObject : public vpObject {
public:
	/*--------------------------------------------------------------------------
		Constructor
	............................................................................
		Automatically load scene graph from file
	*/
	LoadedObject(const char* sFileName);

	/*--------------------------------------------------------------------------
		removeNode()
	............................................................................
		The first parameter is the pointer to the node to be removed.
		Returns vsgu::SUCCESS if success, returns vsgu::FAILURE	if unable to 
		remove the node.
	*/
	int RemoveNode(vsNode* pkNode);

	/*--------------------------------------------------------------------------
		replaceNode()
	............................................................................
		The first parameter is the pointer to the node to be replaced, the 
		second parameter is the pointer to the replacement node.
		Returns vsgu::SUCCESS if success, otherwise returns vsgu::FAILURE.
	*/
	int ReplaceNode(vsNode* pkReplaced, vsNode* pkReplacement);

	/*--------------------------------------------------------------------------
		updateNamedNodes()
	............................................................................
		Updates and print the named node list.
	*/
    void UpdateNamedNodes(bool bDoPrint=false);

protected:

	/*--------------------------------------------------------------------------
		loadObject()
	............................................................................
		Loads an object from the specified file.
		Returns vsgu::SUCCESS if success, otherwise returns vsgu::FAILURE. 
	*/
	int LoadObject(const char* sFileName);
 
};

#endif
