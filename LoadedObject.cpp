#include <vsNode.h>
#include <vuVector.h>
#include <vsNodeLoader.h>
#include <vsNodeFactory.h>
#include <vsgn_builder.h>
#include <vsGeometryBase.h>
#include <LoadedObject.h>
#include <vsTraversalClean.h>
#include <vsTraversalFlatten.h>
#include <DebugUtil.h>

/*==============================================================================
    Member function implementation
*/

/*------------------------------------------------------------------------------
    Constructor
*/
LoadedObject::LoadedObject(const char* sFileName) : vpObject()
{
    // To make sure that Vega Prime does not automatically page in this
    // object when it's added to the scene graph.
    setAutoPage(AUTO_PAGE_OFF);

    LoadObject(sFileName);
	UpdateNamedNodes();
}

/*------------------------------------------------------------------------------
    removeNode()    
*/
int LoadedObject::RemoveNode(vsNode* pkNode)
{
    if (NULL == pkNode)
    {
        return vsgu::FAILURE;
    }

    // If the node needs to be kept 'alive', call node->ref() before it is 
    // erased from parents. And then call node->unref() after
    // it is reattached to the scene. Note that a node is referenced when 
    // it is attached to the scene; a node is unreferenced when it is detached 
    // from the the scene.
    vsNode::const_iterator_parent kParent = pkNode->begin_parent();
    
	while (kParent != pkNode->end_parent())
    {
        (*kParent)->erase_child(pkNode);
        kParent = pkNode->begin_parent();
    }
    
    return vsgu::SUCCESS;
}

/*------------------------------------------------------------------------------
    replaceNode()
*/
int LoadedObject::ReplaceNode(vsNode* pkReplaced, vsNode* pkReplacement)
{
    ASSERT(pkReplaced)
    ASSERT(pkReplacement)

    vpGeometry::const_iterator_named kNamedBegin = begin_named();
    vpGeometry::const_iterator_named kNamedEnd   = end_named();
    vpGeometry::const_iterator_named kNamed;

    for (kNamed = kNamedBegin; kNamed != kNamedEnd; kNamed++) 
    {   
        if (pkReplaced == *kNamed) 
        {
            // no need to reparent
            replace_named(pkReplacement, kNamed, false);
        }
    }

    return vsgu::SUCCESS;
}

/*------------------------------------------------------------------------------
    loadObject()
*/
int LoadedObject::LoadObject(const char* sFileName)
{  
    if (NULL == sFileName) 
    {
        VUNOTIFY_PRINT((vuNotify::LEVEL_WARN, NULL, 
                       "vpGeometry::load - File name is not set."));
        return vsgu::FAILURE;
    }                           

     // Get file extention
    const char* sExtention = crt::strchr(sFileName, '.');
    if ( NULL == sExtention  ) 
    {
        VUNOTIFY_PRINT((vuNotify::LEVEL_WARN, NULL,
             "vpGeometry::load"
             " - Unable to determine file extention; file not loaded."));

        return vsgu::FAILURE;
    }                           

    vsNodeFactory* pkNodeFactory = new vsNodeFactory();
    
	ASSERT(pkNodeFactory)
    
	pkNodeFactory->ref();

    // Get loader based on file type.
    vsNodeLoader* pkLoader = pkNodeFactory->getLoader(sExtention, true);

    if (NULL == pkLoader) 
    {     
        VUNOTIFY_PRINT((vuNotify::LEVEL_WARN, NULL,
                       "vpGeometry::load - Unable to get vsNodeLoader."));
        return vsgu::FAILURE;
    }          
    
	setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_COMBINE_LODS, false);
	setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NAMES, true);
    setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NODES,true);
	setPostLoadOption(vpGeometryPageable::POST_LOAD_OPTION_MERGE_GEOMETRIES, false);

    // Users can manually create scene graph rather than reading 
    // from file. Either way, the root of the scene shall 
    // be stored in m_pNode.
    setVsNode(static_cast<vsNode*> (pkNodeFactory->read(sFileName,getLoaderData())));

    pkNodeFactory->unref();

    if (NULL == getRootNode()) 
    {
        VUNOTIFY_PRINT((vuNotify::LEVEL_WARN, NULL, 
                       "vpGeometry::load - Fail to load the vsNode."));
        return vsgu::FAILURE;
    }                            

    vsFlatten(getRootNode());
    vsClean(getRootNode());
    
    // The root node needs to be a child of this vpObject.
    push_back_child(getRootNode());

    return vsgu::SUCCESS;
}

/*------------------------------------------------------------------------------
    updateNamedNodes()
*/
void LoadedObject::UpdateNamedNodes(bool bDoPrint) 
{
    rebuild_all();

    if (bDoPrint)
    {
        vpGeometryPageable::const_iterator_named kIter = begin_named();

        printf("Named nodes\n");
        int index = 1;
        for (; kIter != end_named(); kIter++) 
        {
            printf("\tindex[ %d ] %s\n", index, (*kIter)->getName());
            ++index;
        }
    }
}
