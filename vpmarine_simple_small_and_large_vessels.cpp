//
// This file was automatically generated from C:/Users/Admin/Desktop/CraneTemp/vpmarine_simple_small_and_large_vessels.acf
//
#include "vpModule.h"
#include "vpKernel.h"
#include "vpSearchPath.h"
#include "vpPipeline.h"
#include "vpWindow.h"
#include "vpChannel.h"
#include "vpObserver.h"
#include "vpScene.h"
#include "vpObject.h"
#include "vpRecyclingService.h"
#include "vpShaderInfrastructure.h"
#include "vpEnvGlobals.h"
#include "vpEnv.h"
#include "vpEnvSun.h"
#include "vpEnvMoon.h"
#include "vpEnvSkyDome.h"
#include "vpEnvCloudLayer.h"
#include "vpEnvWind.h"
#include "vpMotionDrive.h"
#include "vpMotionUFO.h"
#include "vpMotionTetherSpin.h"
#include "vpMarineWaveGeneratorFFT.h"
#include "vpMarineOceanObserverCentered.h"
#include "vpMarineShip.h"
#include "vpMarineShipMotionStrategy.h"
#include "vpMarineFxBowWaveAngled.h"
#include "vpMarineFxSternWake.h"
#include "vpMarineFxHullWake.h"
#include "vpApp.h"

//
// Define a static list to hold the instances we create, so that we 
// can unref them when unconfigure is called
//
typedef vuVector< vuField< vuBase* > > InstancesList;
static InstancesList* s_pInstancesToUnref = NULL;

class myApp : public vpApp,
              public vpInputSourceBoolean::Subscriber,
              public vpInputSourceFloat::Subscriber,
              public vpInputSourceInteger::Subscriber {

public:

    /**
     * Constructor
     */
    myApp() : m_mouse(NULL)
    {}

    /**
     * Destructor
     */
    ~myApp() 
    {

        // remove the subscribers
        vpInputMouse::const_iterator_source_boolean bit;
        for (bit=m_mouse->begin_source_boolean();
             bit!=m_mouse->end_source_boolean();++bit) {
            (*bit)->removeSubscriber(
                vpInputSourceBoolean::EVENT_VALUE_CHANGED, this, true);
        }

        vpInputMouse::const_iterator_source_float fit;
        for (fit=m_mouse->begin_source_float();
             fit!=m_mouse->end_source_float();++fit) {
            (*fit)->removeSubscriber(
                vpInputSourceFloat::EVENT_VALUE_CHANGED, this, true);
        }

        vpInputMouse::const_iterator_source_integer iit;
        for (iit=m_mouse->begin_source_integer();
             iit!=m_mouse->end_source_integer();++iit) {
            (*iit)->removeSubscriber(
                vpInputSourceInteger::EVENT_VALUE_CHANGED, this, true);
        }

        // unreference member variables which cache Vega Prime class instances
        m_mouse->unref();

    }

    /**
     * Configure my app
     */
    int configure() {

        // pre-configuration 


        // configure vega prime system first
        vpApp::configure();


        // post-configuration

        // Increase the reference count by one for all member variables which
        // cache the Vega Prime class instances.
        // 
        // All VSG/Vega Prime class instances are referenced counted. 
        // The initial reference count is 0 after the instance is created. 
        // When the reference count is smaller or equal to 0 in unref(), 
        // the instance will be deleted automatically. Increasing reference
        // count here for all member variables will guarantee that they will
        // not be deleted until myApp is deleted.

        // grab our mouse input from the first window
        vpWindow* window = vpWindow::empty() ? NULL : *vpWindow::begin();
        assert(window);

        vpChannel* channel = vpChannel::empty() ? NULL : *vpChannel::begin();
        assert(channel);

        // create a mouse
        m_mouse = new vpInputMouse();
        m_mouse->setWindow(window);
        m_mouse->setChannel(channel);
        m_mouse->ref();

        // add subscribers to the input sources so we know when a value
        // has changed
        vpInputMouse::const_iterator_source_boolean bit;
        for (bit=m_mouse->begin_source_boolean();
             bit!=m_mouse->end_source_boolean();++bit) {
            (*bit)->addSubscriber(
                vpInputSourceBoolean::EVENT_VALUE_CHANGED, this);
        }

        vpInputMouse::const_iterator_source_float fit;
        for (fit=m_mouse->begin_source_float();
             fit!=m_mouse->end_source_float();++fit) {
            (*fit)->addSubscriber(
                vpInputSourceFloat::EVENT_VALUE_CHANGED, this);
        }

        vpInputMouse::const_iterator_source_integer iit;
        for (iit=m_mouse->begin_source_integer();
             iit!=m_mouse->end_source_integer();++iit) {
            (*iit)->addSubscriber(
                vpInputSourceInteger::EVENT_VALUE_CHANGED, this);
        }

        return vsgu::SUCCESS;

    }


    /**
     * notify method to catch boolean source subscriber events
     */
    void notify(vpInputSourceBoolean::Event, vpInputSourceBoolean *source)
    {
        printf("source %s %s\n", source->getName(),
            source->getValue() ? "pressed" : "released");
    }
    
    /**
     * notify method to catch float source subscriber events
     */
    void notify(vpInputSourceFloat::Event, vpInputSourceFloat *source)
    {
        printf("source %s value %g\n", source->getName(), source->getValue());
    }

    /**
     * notify method to catch integer source subscriber events
     */
    void notify(vpInputSourceInteger::Event, vpInputSourceInteger *source)
    {
        printf("source %s value %d\n", source->getName(), source->getValue());
    }

private:

    vpInputMouse *m_mouse;

};

void define( void )
{
    // Create static instances list that we use to track what we create
    s_pInstancesToUnref = new InstancesList;

    //
    // Initialize all modules
    //

    vpModule::initializeModule( "vpEnv" );
    vpModule::initializeModule( "vpMotion" );
    vpModule::initializeModule( "vpMarine" );


    //
    // Create all instances
    //

    vpKernel* pKernel_myKernel = vpKernel::instance();
    pKernel_myKernel->setNotifyLevel( vuNotify::LEVEL_WARN );
    pKernel_myKernel->setNotifyColorEnable( false );
    pKernel_myKernel->setPriority( vuThread::PRIORITY_NORMAL );
    pKernel_myKernel->setProcessor( -1 );
    pKernel_myKernel->setFrameRateLimiterEnable( true );
    pKernel_myKernel->setDesiredFrameRate( 60 );
    pKernel_myKernel->setNotifyClassTypeMode( vuNotify::CLASS_TYPE_MODE_INCLUSIVE );

    vpSearchPath* pSearchPath_mySearchPath = vpSearchPath::instance();
    pSearchPath_mySearchPath->append( "$(PRESAGIS_VEGA_PRIME_RESOURCE_5)/resources/data/models/tugboat" );
    pSearchPath_mySearchPath->append( "$(PRESAGIS_VEGA_PRIME_RESOURCE_5)/resources/data/models/arleighburke" );

    vpPipeline* pPipeline_myPipeline = new vpPipeline();
    pPipeline_myPipeline->setName( "myPipeline" );
    pPipeline_myPipeline->setMultiThread( vsPipeline::MULTITHREAD_CULL_DRAW );
    pPipeline_myPipeline->setId( 0 );
    pPipeline_myPipeline->setNumCullThreads( 0 );
    pPipeline_myPipeline->setCullThreadPriority( vuThread::PRIORITY_NORMAL );
    pPipeline_myPipeline->setCullThreadProcessor( -1 );
    pPipeline_myPipeline->setDrawThreadPriority( vuThread::PRIORITY_NORMAL );
    pPipeline_myPipeline->setDrawThreadProcessor( -1 );
    pPipeline_myPipeline->setBeginFrameOnVsyncEnable( false );
    pPipeline_myPipeline->setDesiredTextureSubloadTime( -1 );
    pPipeline_myPipeline->setDesiredBufferObjectSubloadTime( -1 );
    pPipeline_myPipeline->setDesiredShaderApplyTime( -1 );
    pPipeline_myPipeline->setTextureSubloadByteAmount( -1 );
    pPipeline_myPipeline->setBufferObjectSubloadByteAmount( -1 );
    pPipeline_myPipeline->setTextureSubloadingGain( 1 );
    pPipeline_myPipeline->setBufferObjectSubloadingGain( 1 );
    pPipeline_myPipeline->setGraphicsResourceApplyThreadMode( vsPipeline::APPLY_ASYNCHRONOUS_GRAPHICS ,  false );
    pPipeline_myPipeline->setGraphicsResourceApplyThreadMode( vsPipeline::APPLY_ASYNCHRONOUS_TEXTURE_SUBLOAD ,  false );
    pPipeline_myPipeline->setGraphicsResourceApplyThreadMode( vsPipeline::APPLY_ASYNCHRONOUS_BUFFER_OBJECT_SUBLOAD ,  false );
    pPipeline_myPipeline->setGraphicsResourceThreadPriority( vuThread::PRIORITY_ABOVE_NORMAL );
    pPipeline_myPipeline->setGraphicsResourceThreadProcessor( -1 );

    s_pInstancesToUnref->push_back( pPipeline_myPipeline );

    vpWindow* pWindow_myWindow = new vpWindow();
    pWindow_myWindow->setName( "myWindow" );
    pWindow_myWindow->setLabel( "Vega Prime Window" );
    pWindow_myWindow->setOrigin( 0 ,  0 );
    pWindow_myWindow->setSize( 1280 ,  1024 );
    pWindow_myWindow->setFullScreenEnable( false );
    pWindow_myWindow->setBorderEnable( true );
    pWindow_myWindow->setInputEnable( true );
    pWindow_myWindow->setCursorEnable( true );
    pWindow_myWindow->setStereoEnable( false );
    pWindow_myWindow->setNumColorBits( 8 );
    pWindow_myWindow->setNumAlphaBits( 8 );
    pWindow_myWindow->setNumDepthBits( 32 );
    pWindow_myWindow->setNumStencilBits( 4 );
    pWindow_myWindow->setNumAccumColorBits( 8 );
    pWindow_myWindow->setNumAccumAlphaBits( 8 );
    pWindow_myWindow->setNumMultiSampleBits( 8 );
    pWindow_myWindow->setSwapInterval( 1 );
    pWindow_myWindow->setSwapSyncEnable( false );
    pWindow_myWindow->setPixelBufferMode( vrDrawContext::PIXEL_BUFFER_MODE_OFF );

    s_pInstancesToUnref->push_back( pWindow_myWindow );

    vpChannel* pChannel_myChannel = new vpChannel();
    pChannel_myChannel->setName( "myChannel" );
    pChannel_myChannel->setOffsetTranslate( 0 ,  0 ,  0 );
    pChannel_myChannel->setOffsetRotate( 0 ,  0 ,  0 );
    pChannel_myChannel->setCullMask( 0x0FFFFFFFF );
    pChannel_myChannel->setRenderMask( 0x0FFFFFFFF );
    pChannel_myChannel->setClearColor( 0.000000f ,  0.500000f ,  1.000000f ,  0.000000f );
    pChannel_myChannel->setClearBuffers( 0x03 );
    pChannel_myChannel->setDrawArea( 0 ,  1 ,  0 ,  1 );
    pChannel_myChannel->setFOVSymmetric( 30.000000f ,  -1.000000f );
    pChannel_myChannel->setNearFar( 1.000000f ,  35000.000000f );
    pChannel_myChannel->setLODVisibilityRangeScale( 1 );
    pChannel_myChannel->setLODTransitionRangeScale( 1 );
    pChannel_myChannel->setFOVScale( -1 );
    pChannel_myChannel->setCullThreadPriority( vuThread::PRIORITY_NORMAL );
    pChannel_myChannel->setCullThreadProcessor( -1 );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_WIREFRAME ,  false );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_TRANSPARENCY ,  true );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_TEXTURE ,  true );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_LIGHT ,  true );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_FOG ,  true );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_SHADERS ,  true );
    pChannel_myChannel->setLightPointThreadPriority( vuThread::PRIORITY_NORMAL );
    pChannel_myChannel->setLightPointThreadProcessor( -1 );
    pChannel_myChannel->setMultiSample( vpChannel::MULTISAMPLE_ANTIALIAS_AND_TRANSPARENCY );
    pChannel_myChannel->setStatisticsPage( vpChannel::PAGE_OFF );
    pChannel_myChannel->setCullBoundingBoxTestEnable( false );
    pChannel_myChannel->setOpaqueSort( vpChannel::OPAQUE_SORT_TEXTURE ,  vpChannel::OPAQUE_SORT_MATERIAL );
    pChannel_myChannel->setTransparentSort( vpChannel::TRANSPARENT_SORT_DEPTH );
    pChannel_myChannel->setDrawBuffer( vpChannel::DRAW_BUFFER_DEFAULT );
    pChannel_myChannel->setStressEnable( false );
    pChannel_myChannel->setStressParameters( 1 ,  20 ,  0.75 ,  0.5 ,  2 );

    s_pInstancesToUnref->push_back( pChannel_myChannel );

    vpObserver* pObserver_Observer = new vpObserver();
    pObserver_Observer->setName( "Observer" );
    pObserver_Observer->setStrategyEnable( true );
    pObserver_Observer->setTranslate( 0 ,  0 ,  30 );
    pObserver_Observer->setRotate( 0 ,  0 ,  0 );
    pObserver_Observer->setLatencyCriticalEnable( false );

    s_pInstancesToUnref->push_back( pObserver_Observer );

    vpScene* pScene_myScene = new vpScene();
    pScene_myScene->setName( "myScene" );

    s_pInstancesToUnref->push_back( pScene_myScene );

    vpObject* pObject_ShipObj_Tugboat = new vpObject();
    pObject_ShipObj_Tugboat->setName( "ShipObj_Tugboat" );
    pObject_ShipObj_Tugboat->setCullMask( 0x0FFFFFFFF );
    pObject_ShipObj_Tugboat->setRenderMask( 0x0FFFFFFFF );
    pObject_ShipObj_Tugboat->setIsectMask( 0x0FFFFFFFF );
    pObject_ShipObj_Tugboat->setStrategyEnable( true );
    pObject_ShipObj_Tugboat->setTranslate( -72 ,  11 ,  0 );
    pObject_ShipObj_Tugboat->setRotate( 0 ,  0 ,  0 );
    pObject_ShipObj_Tugboat->setScale( 1 ,  1 ,  1 );
    pObject_ShipObj_Tugboat->setStaticEnable( false );
    pObject_ShipObj_Tugboat->setFileName( "tugboat.flt" );
    pObject_ShipObj_Tugboat->setAutoPage( vpObject::AUTO_PAGE_SYNCHRONOUS );
    pObject_ShipObj_Tugboat->setManualLODChild( -1 );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_COMBINE_LIGHT_POINTS ,  true );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_COMBINE_LODS ,  true );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_IGNORE_DOF_CONSTRAINTS ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_EXTERNAL_REF_FLAGS ,  true );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NAMES ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NODES ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_QUADS ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_ALL_GEOMETRIES_LIT ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_USE_MATERIAL_DIFFUSE_COLOR ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_MONOCHROME ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_CREATE_ANIMATIONS ,  true );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS ,  true );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS ,  true );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES ,  true );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SURFACE_ATTRIBUTES ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_GENERATE_HIDDEN_POLYGONS ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_CREATE_BUILDINGS ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE ,  false );
    pObject_ShipObj_Tugboat->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SURFACE_MATERIAL_CODE ,  false );
    pObject_ShipObj_Tugboat->setLoaderDetailMultiTextureStage( -1 );
    pObject_ShipObj_Tugboat->setLoaderBlendTolerance( 0.050000f );
    pObject_ShipObj_Tugboat->setLoaderUnits( vsNodeLoader::Data::LOADER_UNITS_METERS );
    pObject_ShipObj_Tugboat->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_OPTIMIZE_GEOMETRIES ,  true );
    pObject_ShipObj_Tugboat->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_COLLAPSE_BINDINGS ,  true );
    pObject_ShipObj_Tugboat->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_ShipObj_Tugboat->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_MAKE_INDEXED ,  true );
    pObject_ShipObj_Tugboat->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_ORTHONORMALIZATION ,  false );
    pObject_ShipObj_Tugboat->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_PARITY_CHECK ,  true );
    pObject_ShipObj_Tugboat->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_HARD_EDGE_CHECK ,  true );
    pObject_ShipObj_Tugboat->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_OPTIMIZE_SMART_MESHES ,  true );
    pObject_ShipObj_Tugboat->setBuilderNormalMode( vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE );
    pObject_ShipObj_Tugboat->setBuilderTangentMode( vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED );
    pObject_ShipObj_Tugboat->setBuilderTangentGenerationMode( vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED );
    pObject_ShipObj_Tugboat->setBuilderColorTolerance( 0.001000f );
    pObject_ShipObj_Tugboat->setBuilderNormalTolerance( 0.860000f );
    pObject_ShipObj_Tugboat->setGeometryOption( vsNodeLoader::Data::GEOMETRY_OPTION_GENERATE_DISPLAY_LISTS ,  true );
    pObject_ShipObj_Tugboat->setGeometryFormat( vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT ,  0x0FFF );
    pObject_ShipObj_Tugboat->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_FLATTEN ,  true );
    pObject_ShipObj_Tugboat->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_CLEAN ,  true );
    pObject_ShipObj_Tugboat->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_MERGE_GEOMETRIES ,  true );
    pObject_ShipObj_Tugboat->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_BINDINGS ,  true );
    pObject_ShipObj_Tugboat->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_ShipObj_Tugboat->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_VALIDATE ,  false );
    pObject_ShipObj_Tugboat->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_MAKE_INDEXED ,  true );
    pObject_ShipObj_Tugboat->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_SCRUB ,  false );
    pObject_ShipObj_Tugboat->setTextureSubloadEnable( false );
    pObject_ShipObj_Tugboat->setBufferObjectSubloadEnable( true );
    pObject_ShipObj_Tugboat->setTextureSubloadRender( vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED );
    pObject_ShipObj_Tugboat->setTexturePreserveImageLevelsEnable( true );

    s_pInstancesToUnref->push_back( pObject_ShipObj_Tugboat );

    vpObject* pObject_ShipObj_AB = new vpObject();
    pObject_ShipObj_AB->setName( "ShipObj_AB" );
    pObject_ShipObj_AB->setCullMask( 0x0FFFFFFFF );
    pObject_ShipObj_AB->setRenderMask( 0x0FFFFFFFF );
    pObject_ShipObj_AB->setIsectMask( 0x0FFFFFFFF );
    pObject_ShipObj_AB->setStrategyEnable( true );
    pObject_ShipObj_AB->setTranslate( 0 ,  -75 ,  0 );
    pObject_ShipObj_AB->setRotate( 0 ,  0 ,  0 );
    pObject_ShipObj_AB->setScale( 1 ,  1 ,  1 );
    pObject_ShipObj_AB->setStaticEnable( false );
    pObject_ShipObj_AB->setFileName( "arleighburke.flt" );
    pObject_ShipObj_AB->setAutoPage( vpObject::AUTO_PAGE_SYNCHRONOUS );
    pObject_ShipObj_AB->setManualLODChild( -1 );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_COMBINE_LIGHT_POINTS ,  true );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_COMBINE_LODS ,  true );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_IGNORE_DOF_CONSTRAINTS ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_EXTERNAL_REF_FLAGS ,  true );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NAMES ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NODES ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_QUADS ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_ALL_GEOMETRIES_LIT ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_USE_MATERIAL_DIFFUSE_COLOR ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_MONOCHROME ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_CREATE_ANIMATIONS ,  true );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS ,  true );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS ,  true );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES ,  true );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SURFACE_ATTRIBUTES ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_GENERATE_HIDDEN_POLYGONS ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_CREATE_BUILDINGS ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE ,  false );
    pObject_ShipObj_AB->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SURFACE_MATERIAL_CODE ,  false );
    pObject_ShipObj_AB->setLoaderDetailMultiTextureStage( -1 );
    pObject_ShipObj_AB->setLoaderBlendTolerance( 0.050000f );
    pObject_ShipObj_AB->setLoaderUnits( vsNodeLoader::Data::LOADER_UNITS_METERS );
    pObject_ShipObj_AB->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_OPTIMIZE_GEOMETRIES ,  true );
    pObject_ShipObj_AB->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_COLLAPSE_BINDINGS ,  true );
    pObject_ShipObj_AB->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_ShipObj_AB->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_MAKE_INDEXED ,  true );
    pObject_ShipObj_AB->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_ORTHONORMALIZATION ,  false );
    pObject_ShipObj_AB->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_PARITY_CHECK ,  true );
    pObject_ShipObj_AB->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_HARD_EDGE_CHECK ,  true );
    pObject_ShipObj_AB->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_OPTIMIZE_SMART_MESHES ,  true );
    pObject_ShipObj_AB->setBuilderNormalMode( vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE );
    pObject_ShipObj_AB->setBuilderTangentMode( vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED );
    pObject_ShipObj_AB->setBuilderTangentGenerationMode( vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED );
    pObject_ShipObj_AB->setBuilderColorTolerance( 0.001000f );
    pObject_ShipObj_AB->setBuilderNormalTolerance( 0.860000f );
    pObject_ShipObj_AB->setGeometryOption( vsNodeLoader::Data::GEOMETRY_OPTION_GENERATE_DISPLAY_LISTS ,  false );
    pObject_ShipObj_AB->setGeometryFormat( vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT ,  0x0FFF );
    pObject_ShipObj_AB->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_FLATTEN ,  true );
    pObject_ShipObj_AB->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_CLEAN ,  true );
    pObject_ShipObj_AB->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_MERGE_GEOMETRIES ,  true );
    pObject_ShipObj_AB->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_BINDINGS ,  true );
    pObject_ShipObj_AB->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_ShipObj_AB->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_VALIDATE ,  false );
    pObject_ShipObj_AB->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_MAKE_INDEXED ,  true );
    pObject_ShipObj_AB->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_SCRUB ,  false );
    pObject_ShipObj_AB->setTextureSubloadEnable( false );
    pObject_ShipObj_AB->setBufferObjectSubloadEnable( true );
    pObject_ShipObj_AB->setTextureSubloadRender( vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED );
    pObject_ShipObj_AB->setTexturePreserveImageLevelsEnable( true );

    s_pInstancesToUnref->push_back( pObject_ShipObj_AB );

    vpRecyclingService* pRecyclingService_myRecyclingService = vpRecyclingService::instance();
    pRecyclingService_myRecyclingService->setMultiThread( vpRecyclingService::MULTITHREAD_INLINE );
    pRecyclingService_myRecyclingService->setThreadPriority( vuThread::PRIORITY_NORMAL );
    pRecyclingService_myRecyclingService->setThreadProcessor( -1 );
    pRecyclingService_myRecyclingService->setRecycleTime( -1 );

    vpShaderInfrastructure* pShaderInfrastructure_myShaderInfrastructure = vpShaderInfrastructure::instance();
    pShaderInfrastructure_myShaderInfrastructure->setMode( vrShaderInfrastructure::MODE_REPLACE_SHADERS );

    vpEnvGlobals* pEnvGlobals_myEnvGlobals = vpEnvGlobals::instance();
    pEnvGlobals_myEnvGlobals->setSkyLightEnable( true );
    pEnvGlobals_myEnvGlobals->setDominantCelestialLightingEnable( true );
    pEnvGlobals_myEnvGlobals->setLocalViewerEnable( false );
    pEnvGlobals_myEnvGlobals->setTwoSidedLightingEnable( false );
    pEnvGlobals_myEnvGlobals->setEnvironmentMapGenerationEnable( false );

    vpEnv* pEnv_myEnv = new vpEnv();
    pEnv_myEnv->setName( "myEnv" );
    pEnv_myEnv->setDate( 22 ,  6 ,  2002 );
    pEnv_myEnv->setTimeOfDay( 11.010000f );
    pEnv_myEnv->setTimeMultiplier( 1.000000f );
    pEnv_myEnv->setEphemerisUpdateInterval( 0.000000f );
    pEnv_myEnv->setReferencePosition( -96.790001f ,  32.790001f );
    pEnv_myEnv->setEphemerisTimeZoneOffset( -10000 );
    pEnv_myEnv->setSkyColor( 0.513725f ,  0.701961f ,  0.941176f ,  1.000000f );
    pEnv_myEnv->setVisibilityType( vpEnvFx::VISIBILITY_TYPE_PIXEL_EXP2 );
    pEnv_myEnv->setVisibilityRangeOnset( 0.000000f );
    pEnv_myEnv->setVisibilityRangeOpaque( 25000.000000f );
    pEnv_myEnv->setVisibilityColor( 0.764706f ,  0.858824f ,  1.000000f ,  1.000000f );
    pEnv_myEnv->setHazeColor( 0.772549f ,  0.772549f ,  0.772549f ,  0.445397f );
    pEnv_myEnv->setManageVisibilityColorsEnable( true );
    pEnv_myEnv->setAmbientLightingColor( 0.000000f ,  0.000000f ,  0.000000f ,  1.000000f );
    pEnv_myEnv->setLightBrightnessScale( vpEnv::COLOR_AMBIENT ,  0.500000f );
    pEnv_myEnv->setLightBrightnessScale( vpEnv::COLOR_DIFFUSE ,  0.500000f );
    pEnv_myEnv->setLightBrightnessScale( vpEnv::COLOR_SPECULAR ,  1.000000f );
    pEnv_myEnv->setLightColorScale( vpEnv::COLOR_AMBIENT ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnv_myEnv->setLightColorScale( vpEnv::COLOR_DIFFUSE ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnv_myEnv->setLightColorScale( vpEnv::COLOR_SPECULAR ,  1.000000f ,  1.000000f ,  1.000000f );

    s_pInstancesToUnref->push_back( pEnv_myEnv );

    vpEnvSun* pEnvSun_myEnvSun = new vpEnvSun();
    pEnvSun_myEnvSun->setName( "myEnvSun" );
    pEnvSun_myEnvSun->setEnable( true );
    pEnvSun_myEnvSun->setTwilightDip( -12.000000f );
    pEnvSun_myEnvSun->setGeometryEnable( true );
    pEnvSun_myEnvSun->setTextureFile( "sun.inta" );
    pEnvSun_myEnvSun->setTextureBlendColor( 1.000000f ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnvSun_myEnvSun->setTextureBlendMode( vpEnvSun::TEXTURE_BLEND_MODE_MODULATE );
    pEnvSun_myEnvSun->setColor( 0.992156f ,  1.000000f ,  0.949019f ,  1.000000f );
    pEnvSun_myEnvSun->setVisibilityRangeRatio( 0.100000f );
    pEnvSun_myEnvSun->setAngularSize( 5.500000f );
    pEnvSun_myEnvSun->setHorizonAngle( 40.000000f );
    pEnvSun_myEnvSun->setHorizonColor( 1.000000f ,  0.905882f ,  0.686275f ,  1.000000f );
    pEnvSun_myEnvSun->setHorizonSizeScale( 2.000000f );
    pEnvSun_myEnvSun->setHorizonLightColorScale( 0.250000f );

    s_pInstancesToUnref->push_back( pEnvSun_myEnvSun );

    vpEnvMoon* pEnvMoon_myEnvMoon = new vpEnvMoon();
    pEnvMoon_myEnvMoon->setName( "myEnvMoon" );
    pEnvMoon_myEnvMoon->setEnable( true );
    pEnvMoon_myEnvMoon->setBrightness( 0.250000f );
    pEnvMoon_myEnvMoon->setGeometryEnable( true );
    pEnvMoon_myEnvMoon->setTextureFile( "moon.inta" );
    pEnvMoon_myEnvMoon->setTextureBlendColor( 1.000000f ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnvMoon_myEnvMoon->setTextureBlendMode( vpEnvMoon::TEXTURE_BLEND_MODE_MODULATE );
    pEnvMoon_myEnvMoon->setColor( 0.811765f ,  0.886275f ,  0.937255f ,  1.000000f );
    pEnvMoon_myEnvMoon->setVisibilityRangeRatio( 0.200000f );
    pEnvMoon_myEnvMoon->setAngularSize( 1.500000f );
    pEnvMoon_myEnvMoon->setHorizonAngle( 30.000000f );
    pEnvMoon_myEnvMoon->setHorizonColor( 0.811765f ,  0.886275f ,  0.937255f ,  1.000000f );
    pEnvMoon_myEnvMoon->setHorizonSizeScale( 1.700000f );
    pEnvMoon_myEnvMoon->setHorizonLightColorScale( 0.000000f );

    s_pInstancesToUnref->push_back( pEnvMoon_myEnvMoon );

    vpEnvSkyDome* pEnvSkyDome_myEnvSkyDome = new vpEnvSkyDome();
    pEnvSkyDome_myEnvSkyDome->setName( "myEnvSkyDome" );
    pEnvSkyDome_myEnvSkyDome->setEnable( true );
    pEnvSkyDome_myEnvSkyDome->setGroundColor( 0.211765f ,  0.286275f ,  0.149020f ,  1.000000f );
    pEnvSkyDome_myEnvSkyDome->setGroundEnable( true );
    pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio( 0 ,  0.100000f );
    pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio( 1 ,  0.300000f );
    pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio( 2 ,  0.750000f );
    pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio( 3 ,  0.900000f );
    pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio( 4 ,  1.000000f );
    pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio( 5 ,  1.000000f );
    pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio( 6 ,  1.000000f );

    s_pInstancesToUnref->push_back( pEnvSkyDome_myEnvSkyDome );

    vpEnvCloudLayer* pEnvCloudLayer_myEnvCloudLayer = new vpEnvCloudLayer();
    pEnvCloudLayer_myEnvCloudLayer->setName( "myEnvCloudLayer" );
    pEnvCloudLayer_myEnvCloudLayer->setEnable( true );
    pEnvCloudLayer_myEnvCloudLayer->setColor( 0.300000f ,  0.300000f ,  0.300000f ,  1.000000f );
    pEnvCloudLayer_myEnvCloudLayer->setElevation( 5000.000000f ,  6000.000000f );
    pEnvCloudLayer_myEnvCloudLayer->setTransitionRange( 500.000000f ,  500.000000f );
    pEnvCloudLayer_myEnvCloudLayer->setScudEnable( false );
    pEnvCloudLayer_myEnvCloudLayer->setTextureFile( "" );
    pEnvCloudLayer_myEnvCloudLayer->setTextureBlendColor( 1.000000f ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnvCloudLayer_myEnvCloudLayer->setTextureBlendMode( vpEnvCloudLayer::TEXTURE_BLEND_MODE_MODULATE );
    pEnvCloudLayer_myEnvCloudLayer->setTextureTiling( 3.000000f ,  3.000000f );
    pEnvCloudLayer_myEnvCloudLayer->setMinVisibilityScale( 0.000000f );
    pEnvCloudLayer_myEnvCloudLayer->setHorizonColorScale( 1.000000f );
    pEnvCloudLayer_myEnvCloudLayer->setCoverageScale( 0.170000f );
    pEnvCloudLayer_myEnvCloudLayer->setShadowsEnable( false );
    pEnvCloudLayer_myEnvCloudLayer->setShadowsColorPunchThrough( 0.300000f );
    pEnvCloudLayer_myEnvCloudLayer->setShadowIntensity( 0.600000f );
    pEnvCloudLayer_myEnvCloudLayer->setShadowsContribution( 0.100000f ,  0.900000f );

    s_pInstancesToUnref->push_back( pEnvCloudLayer_myEnvCloudLayer );

    vpEnvWind* pEnvWind_myEnvWind = new vpEnvWind();
    pEnvWind_myEnvWind->setName( "myEnvWind" );
    pEnvWind_myEnvWind->setEnable( true );
    pEnvWind_myEnvWind->setSpeed( 0.000000f );
    pEnvWind_myEnvWind->setDirection( 0.000000f ,  1.000000f ,  0.000000f );

    s_pInstancesToUnref->push_back( pEnvWind_myEnvWind );

    vpMotionDrive* pMotionDrive_myMotionDriveTugboat = new vpMotionDrive();
    pMotionDrive_myMotionDriveTugboat->setName( "myMotionDriveTugboat" );
    pMotionDrive_myMotionDriveTugboat->setSpeed( 0.1 );
    pMotionDrive_myMotionDriveTugboat->setSpeedLimits( 0 ,  4 );
    pMotionDrive_myMotionDriveTugboat->setSpeedDelta( 1 ,  1 );
    pMotionDrive_myMotionDriveTugboat->setHeadingDelta( 1 );

    s_pInstancesToUnref->push_back( pMotionDrive_myMotionDriveTugboat );

    vpMotionDrive* pMotionDrive_myMotionDrive_AB = new vpMotionDrive();
    pMotionDrive_myMotionDrive_AB->setName( "myMotionDrive_AB" );
    pMotionDrive_myMotionDrive_AB->setSpeed( 0.1 );
    pMotionDrive_myMotionDrive_AB->setSpeedLimits( 0 ,  4 );
    pMotionDrive_myMotionDrive_AB->setSpeedDelta( 1 ,  1 );
    pMotionDrive_myMotionDrive_AB->setHeadingDelta( 1 );

    s_pInstancesToUnref->push_back( pMotionDrive_myMotionDrive_AB );

    vpMotionUFO* pMotionUFO_myMotionUFO = new vpMotionUFO();
    pMotionUFO_myMotionUFO->setName( "myMotionUFO" );
    pMotionUFO_myMotionUFO->setSpeed( 10 );
    pMotionUFO_myMotionUFO->setBoost( 50 );
    pMotionUFO_myMotionUFO->setBoostTurning( 5 );
    pMotionUFO_myMotionUFO->setRateHeading( 40 );
    pMotionUFO_myMotionUFO->setRatePitch( 20 );

    s_pInstancesToUnref->push_back( pMotionUFO_myMotionUFO );

    vpMotionTetherSpin* pMotionTetherSpin_myMotionTetherSpin = new vpMotionTetherSpin();
    pMotionTetherSpin_myMotionTetherSpin->setName( "myMotionTetherSpin" );
    pMotionTetherSpin_myMotionTetherSpin->setENUBasedEnable( true );
    pMotionTetherSpin_myMotionTetherSpin->setResponseScale( 8 );
    pMotionTetherSpin_myMotionTetherSpin->setInputEnable( true );
    pMotionTetherSpin_myMotionTetherSpin->setRadius( 392 );
    pMotionTetherSpin_myMotionTetherSpin->setAngularRate( -1 );
    pMotionTetherSpin_myMotionTetherSpin->setElevation( 66 );

    s_pInstancesToUnref->push_back( pMotionTetherSpin_myMotionTetherSpin );

    vpMarineWaveGeneratorFFT* pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT = new vpMarineWaveGeneratorFFT();
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setName( "myMarineWaveGeneratorFFT" );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setMeshResolution( 64 ,  64 );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setCellExtents( 82.000000f ,  82.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSeaState( 6 );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSurfaceWindSpeed( 25.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setDominantWaveDirection( 200.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSignificantWaveHeight( 3.352800f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setPeakThreshold( 0.370000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setTextureAnimationFactor( 0.290000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSuppressSmallWavesFactor( 0.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setAlignmentWithWind( 1.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setTravel( 1.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setPowerLawDistribution( 2.130000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setChoppyWavesFactor( 0.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setNormalCalculationsEnable( true );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setFreezeEnable( false );

    s_pInstancesToUnref->push_back( pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT );

    vpMarineOceanObserverCentered* pMarineOceanObserverCentered_OceanObserverCentered = new vpMarineOceanObserverCentered();
    pMarineOceanObserverCentered_OceanObserverCentered->setName( "OceanObserverCentered" );
    pMarineOceanObserverCentered_OceanObserverCentered->setEnable( true );
    pMarineOceanObserverCentered_OceanObserverCentered->setTranslate( 0 ,  0 ,  0 );
    pMarineOceanObserverCentered_OceanObserverCentered->setTideHeight( 20.500000f );
    pMarineOceanObserverCentered_OceanObserverCentered->setAutoTextureSeaStateEnable( false );
    pMarineOceanObserverCentered_OceanObserverCentered->setOverallColor( 0.078000f ,  0.138000f ,  0.190000f ,  1.000000f );
    pMarineOceanObserverCentered_OceanObserverCentered->addLODSwitchDistance( 300 );
    pMarineOceanObserverCentered_OceanObserverCentered->addLODSwitchDistance( 600 );
    pMarineOceanObserverCentered_OceanObserverCentered->addLODSwitchDistance( 900 );
    pMarineOceanObserverCentered_OceanObserverCentered->addLODSwitchDistance( 1200 );
    pMarineOceanObserverCentered_OceanObserverCentered->setFarClipPlane( 2500 );
    pMarineOceanObserverCentered_OceanObserverCentered->setEnvironmentMapTextureFile( "" );
    pMarineOceanObserverCentered_OceanObserverCentered->setLocalReflectionsEnable( true );
    pMarineOceanObserverCentered_OceanObserverCentered->setLocalReflectionsRipplingStrength( 1.000000f );
    pMarineOceanObserverCentered_OceanObserverCentered->setCullMask( 0x0FFFFFFFF );
    pMarineOceanObserverCentered_OceanObserverCentered->setRenderMask( 0x0FFFFFFFF );
    pMarineOceanObserverCentered_OceanObserverCentered->setIsectMask( 0x0FFFFFFFF );

    s_pInstancesToUnref->push_back( pMarineOceanObserverCentered_OceanObserverCentered );

    vpMarineShip* pMarineShip_ShipDef_Tugboat = new vpMarineShip();
    pMarineShip_ShipDef_Tugboat->setName( "ShipDef_Tugboat" );
    pMarineShip_ShipDef_Tugboat->setMaxSpeed( 35.000000f );
    pMarineShip_ShipDef_Tugboat->setBeam( 9.000000f );
    pMarineShip_ShipDef_Tugboat->setWidthAtOrigin( 7.000000f );
    pMarineShip_ShipDef_Tugboat->setMaxTurnRate( 5.500000f );
    pMarineShip_ShipDef_Tugboat->setBowFlareAngle( 45.000000f );
    pMarineShip_ShipDef_Tugboat->setBowOffset( 13.700000f );
    pMarineShip_ShipDef_Tugboat->setBowWidth( 1.500000f );
    pMarineShip_ShipDef_Tugboat->setBowLength( 2.000000f );
    pMarineShip_ShipDef_Tugboat->setBowFreeboard( 3.220000f );
    pMarineShip_ShipDef_Tugboat->setBowStempostAngle( 14.000000f );
    pMarineShip_ShipDef_Tugboat->setBowStempostLength( 1.800000f );
    pMarineShip_ShipDef_Tugboat->setSternOffset( -15.500000f );
    pMarineShip_ShipDef_Tugboat->setSternWidth( 9.000000f );
    pMarineShip_ShipDef_Tugboat->setSternWakeAngle( 7.000000f );
    pMarineShip_ShipDef_Tugboat->setComputeVelocityEnable( true );

    s_pInstancesToUnref->push_back( pMarineShip_ShipDef_Tugboat );

    vpMarineShip* pMarineShip_ShipDef_AB = new vpMarineShip();
    pMarineShip_ShipDef_AB->setName( "ShipDef_AB" );
    pMarineShip_ShipDef_AB->setMaxSpeed( 31.000000f );
    pMarineShip_ShipDef_AB->setBeam( 9.000000f );
    pMarineShip_ShipDef_AB->setWidthAtOrigin( 17.000000f );
    pMarineShip_ShipDef_AB->setMaxTurnRate( 2.000000f );
    pMarineShip_ShipDef_AB->setBowFlareAngle( 16.000000f );
    pMarineShip_ShipDef_AB->setBowOffset( 67.500000f );
    pMarineShip_ShipDef_AB->setBowWidth( 1.000000f );
    pMarineShip_ShipDef_AB->setBowLength( 4.000000f );
    pMarineShip_ShipDef_AB->setBowFreeboard( 3.000000f );
    pMarineShip_ShipDef_AB->setBowStempostAngle( 30.000000f );
    pMarineShip_ShipDef_AB->setBowStempostLength( 15.000000f );
    pMarineShip_ShipDef_AB->setSternOffset( -74.000000f );
    pMarineShip_ShipDef_AB->setSternWidth( 12.500000f );
    pMarineShip_ShipDef_AB->setSternWakeAngle( 7.000000f );
    pMarineShip_ShipDef_AB->setComputeVelocityEnable( true );

    s_pInstancesToUnref->push_back( pMarineShip_ShipDef_AB );

    vpMarineShipMotionStrategy* pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat = new vpMarineShipMotionStrategy();
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat->setName( "myMarineShipMotionStrategy_TugBoat" );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat->setComputeYawEnable( true );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat->setSmoothingFactorPortAndStarboard( 50 );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat->setSmoothingFactorBowAndStern( 90 );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat->setPitchFactor( 1.000000f );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat->setRollFactor( 1.000000f );

    s_pInstancesToUnref->push_back( pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat );

    vpMarineShipMotionStrategy* pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB = new vpMarineShipMotionStrategy();
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB->setName( "myMarineShipMotionStrategy_AB" );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB->setComputeYawEnable( true );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB->setSmoothingFactorPortAndStarboard( 180 );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB->setSmoothingFactorBowAndStern( 180 );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB->setPitchFactor( 1.400000f );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB->setRollFactor( 1.400000f );

    s_pInstancesToUnref->push_back( pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB );

    vpMarineFxBowWaveAngled* pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_Tugboat = new vpMarineFxBowWaveAngled();
    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_Tugboat->setName( "myMarineFxBowWaveAngled_Tugboat" );
    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_Tugboat->setEnable( true );

    s_pInstancesToUnref->push_back( pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_Tugboat );

    vpMarineFxBowWaveAngled* pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_AB = new vpMarineFxBowWaveAngled();
    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_AB->setName( "myMarineFxBowWaveAngled_AB" );
    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_AB->setEnable( true );

    s_pInstancesToUnref->push_back( pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_AB );

    vpMarineFxSternWake* pMarineFxSternWake_myMarineFxSternWake_Tugboat = new vpMarineFxSternWake();
    pMarineFxSternWake_myMarineFxSternWake_Tugboat->setName( "myMarineFxSternWake_Tugboat" );
    pMarineFxSternWake_myMarineFxSternWake_Tugboat->setEnable( true );
    pMarineFxSternWake_myMarineFxSternWake_Tugboat->setDissipationTime( 30.000000f );
    pMarineFxSternWake_myMarineFxSternWake_Tugboat->setTessellationFactor( 1.000000f );
    pMarineFxSternWake_myMarineFxSternWake_Tugboat->setHeightOffset( 0.150000f );

    s_pInstancesToUnref->push_back( pMarineFxSternWake_myMarineFxSternWake_Tugboat );

    vpMarineFxSternWake* pMarineFxSternWake_myMarineFxSternWake_AB = new vpMarineFxSternWake();
    pMarineFxSternWake_myMarineFxSternWake_AB->setName( "myMarineFxSternWake_AB" );
    pMarineFxSternWake_myMarineFxSternWake_AB->setEnable( true );
    pMarineFxSternWake_myMarineFxSternWake_AB->setDissipationTime( 32.000000f );
    pMarineFxSternWake_myMarineFxSternWake_AB->setTessellationFactor( 1.000000f );
    pMarineFxSternWake_myMarineFxSternWake_AB->setHeightOffset( 0.150000f );

    s_pInstancesToUnref->push_back( pMarineFxSternWake_myMarineFxSternWake_AB );

    vpMarineFxHullWake* pMarineFxHullWake_myMarineFxHullWake_Tugboat = new vpMarineFxHullWake();
    pMarineFxHullWake_myMarineFxHullWake_Tugboat->setName( "myMarineFxHullWake_Tugboat" );
    pMarineFxHullWake_myMarineFxHullWake_Tugboat->setEnable( true );
    pMarineFxHullWake_myMarineFxHullWake_Tugboat->setDissipationTime( 8.000000f );
    pMarineFxHullWake_myMarineFxHullWake_Tugboat->setTessellationFactor( 1.000000f );
    pMarineFxHullWake_myMarineFxHullWake_Tugboat->setHeightOffset( 0.150000f );

    s_pInstancesToUnref->push_back( pMarineFxHullWake_myMarineFxHullWake_Tugboat );

    vpMarineFxHullWake* pMarineFxHullWake_myMarineFxHullWake_AB = new vpMarineFxHullWake();
    pMarineFxHullWake_myMarineFxHullWake_AB->setName( "myMarineFxHullWake_AB" );
    pMarineFxHullWake_myMarineFxHullWake_AB->setEnable( true );
    pMarineFxHullWake_myMarineFxHullWake_AB->setDissipationTime( 15.000000f );
    pMarineFxHullWake_myMarineFxHullWake_AB->setTessellationFactor( 1.000000f );
    pMarineFxHullWake_myMarineFxHullWake_AB->setHeightOffset( 0.150000f );

    s_pInstancesToUnref->push_back( pMarineFxHullWake_myMarineFxHullWake_AB );



    //
    // Satisfy all references
    //



    pPipeline_myPipeline->addWindow( pWindow_myWindow );

    pWindow_myWindow->addChannel( pChannel_myChannel );


    pObserver_Observer->setStrategy( pMotionTetherSpin_myMotionTetherSpin );
    pObserver_Observer->addChannel( pChannel_myChannel );
    pObserver_Observer->addAttachment( pEnv_myEnv );
    pObserver_Observer->setScene( pScene_myScene );

    pScene_myScene->addChild( pObject_ShipObj_Tugboat );
    pScene_myScene->addChild( pObject_ShipObj_AB );

    pObject_ShipObj_Tugboat->setStrategy( pMotionDrive_myMotionDriveTugboat );

    pObject_ShipObj_AB->setStrategy( pMotionDrive_myMotionDrive_AB );




    pEnv_myEnv->addEnvFx( pEnvSun_myEnvSun );
    pEnv_myEnv->addEnvFx( pEnvMoon_myEnvMoon );
    pEnv_myEnv->addEnvFx( pEnvSkyDome_myEnvSkyDome );
    pEnv_myEnv->addEnvFx( pEnvCloudLayer_myEnvCloudLayer );
    pEnv_myEnv->addEnvFx( pEnvWind_myEnvWind );






    pMotionDrive_myMotionDriveTugboat->setNextStrategy( pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat );

    pMotionDrive_myMotionDrive_AB->setNextStrategy( pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB );


    pMotionTetherSpin_myMotionTetherSpin->setTetherReference( pObject_ShipObj_AB );


    pMarineOceanObserverCentered_OceanObserverCentered->addObserver( pObserver_Observer );
    pMarineOceanObserverCentered_OceanObserverCentered->setWaveGenerator( pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT );

    pMarineShip_ShipDef_Tugboat->setOcean( pMarineOceanObserverCentered_OceanObserverCentered );
    pMarineShip_ShipDef_Tugboat->setTransform( pObject_ShipObj_Tugboat );

    pMarineShip_ShipDef_AB->setOcean( pMarineOceanObserverCentered_OceanObserverCentered );
    pMarineShip_ShipDef_AB->setTransform( pObject_ShipObj_AB );

    pMarineShipMotionStrategy_myMarineShipMotionStrategy_TugBoat->setShip( pMarineShip_ShipDef_Tugboat );

    pMarineShipMotionStrategy_myMarineShipMotionStrategy_AB->setShip( pMarineShip_ShipDef_AB );

    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_Tugboat->setShip( pMarineShip_ShipDef_Tugboat );

    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled_AB->setShip( pMarineShip_ShipDef_AB );

    pMarineFxSternWake_myMarineFxSternWake_Tugboat->setShip( pMarineShip_ShipDef_Tugboat );

    pMarineFxSternWake_myMarineFxSternWake_AB->setShip( pMarineShip_ShipDef_AB );

    pMarineFxHullWake_myMarineFxHullWake_Tugboat->setShip( pMarineShip_ShipDef_Tugboat );

    pMarineFxHullWake_myMarineFxHullWake_AB->setShip( pMarineShip_ShipDef_AB );

}




void unconfigure( void )
{
    //
    // Unref all created instances
    //

    s_pInstancesToUnref->clear();
    delete s_pInstancesToUnref;
}





//
// Main Program
//

int main(int argc, char *argv[])
{
    // initialize Vega Prime
    vp::initialize(argc, argv);

	// initialize addition modules here
    vpModule::initializeModule("vpinput");

    // create my app instance
    myApp *app = new myApp;

	// load acf file
    if (argc <= 1)
        app->define("vpinput_mouse.acf");
    else
        app->define(argv[1]);

    // use the code generated by LynX Prime
    define();

    // configure my app instance
    app->configure();

    // execute the main runtime loop
    app->run();

    // call the unconfig code generated by LynX Prime
    unconfigure();

    // delete my app instance
    app->unref();

    // shutdown Vega Prime
    vp::shutdown();

    return 0;

}

