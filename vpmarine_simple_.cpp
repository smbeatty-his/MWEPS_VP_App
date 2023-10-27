//
// This file was automatically generated from C:/Presagis/Vega_Prime_5/resources/samples/vegaprime/vpmarine/vpmarine_simple/vpmarine_simple.acf
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
#include "vpMotionUFO.h"
#include "vpMarineWaveGeneratorFFT.h"
#include "vpMarineOceanObserverCentered.h"
#include "vpMarineShip.h"
#include "vpMarineShipMotionStrategy.h"
#include "vpMarineFxBowWaveAngled.h"
#include "vpMarineFxSternWake.h"
#include "vpMarineFxHullWake.h"

//
// Define a static list to hold the instances we create, so that we 
// can unref them when unconfigure is called
//
typedef vuVector< vuField< vuBase* > > InstancesList;
static InstancesList* s_pInstancesToUnref = NULL;



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
    pKernel_myKernel->setFrameRateLimiterEnable( false );
    pKernel_myKernel->setDesiredFrameRate( 0 );
    pKernel_myKernel->setNotifyClassTypeMode( vuNotify::CLASS_TYPE_MODE_INCLUSIVE );

    vpSearchPath* pSearchPath_mySearchPath = vpSearchPath::instance();
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
    pWindow_myWindow->setOrigin( 480 ,  640 );
    pWindow_myWindow->setSize( 640 ,  480 );
    pWindow_myWindow->setFullScreenEnable( false );
    pWindow_myWindow->setBorderEnable( false );
    pWindow_myWindow->setInputEnable( true );
    pWindow_myWindow->setCursorEnable( true );
    pWindow_myWindow->setStereoEnable( false );
    pWindow_myWindow->setNumColorBits( 8 );
    pWindow_myWindow->setNumAlphaBits( 8 );
    pWindow_myWindow->setNumDepthBits( 24 );
    pWindow_myWindow->setNumStencilBits( 0 );
    pWindow_myWindow->setNumAccumColorBits( 0 );
    pWindow_myWindow->setNumAccumAlphaBits( 0 );
    pWindow_myWindow->setNumMultiSampleBits( 4 );
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
    pObserver_Observer->setRotate( -90 ,  0 ,  0 );
    pObserver_Observer->setLatencyCriticalEnable( false );

    s_pInstancesToUnref->push_back( pObserver_Observer );

    vpScene* pScene_myScene = new vpScene();
    pScene_myScene->setName( "myScene" );

    s_pInstancesToUnref->push_back( pScene_myScene );

    vpObject* pObject_ShipObj = new vpObject();
    pObject_ShipObj->setName( "ShipObj" );
    pObject_ShipObj->setCullMask( 0x0FFFFFFFF );
    pObject_ShipObj->setRenderMask( 0x0FFFFFFFF );
    pObject_ShipObj->setIsectMask( 0x0FFFFFFFF );
    pObject_ShipObj->setStrategyEnable( true );
    pObject_ShipObj->setTranslate( 0 ,  0 ,  0 );
    pObject_ShipObj->setRotate( 0 ,  0 ,  0 );
    pObject_ShipObj->setScale( 1 ,  1 ,  1 );
    pObject_ShipObj->setStaticEnable( false );
    pObject_ShipObj->setFileName( "arleighburke.flt" );
    pObject_ShipObj->setAutoPage( vpObject::AUTO_PAGE_SYNCHRONOUS );
    pObject_ShipObj->setManualLODChild( -1 );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_COMBINE_LIGHT_POINTS ,  true );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_COMBINE_LODS ,  true );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_IGNORE_DOF_CONSTRAINTS ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_EXTERNAL_REF_FLAGS ,  true );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NAMES ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NODES ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_QUADS ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_ALL_GEOMETRIES_LIT ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_USE_MATERIAL_DIFFUSE_COLOR ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_MONOCHROME ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_CREATE_ANIMATIONS ,  true );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS ,  true );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS ,  true );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES ,  true );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SURFACE_ATTRIBUTES ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_GENERATE_HIDDEN_POLYGONS ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_CREATE_BUILDINGS ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE ,  false );
    pObject_ShipObj->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SURFACE_MATERIAL_CODE ,  false );
    pObject_ShipObj->setLoaderDetailMultiTextureStage( -1 );
    pObject_ShipObj->setLoaderBlendTolerance( 0.050000f );
    pObject_ShipObj->setLoaderUnits( vsNodeLoader::Data::LOADER_UNITS_METERS );
    pObject_ShipObj->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_OPTIMIZE_GEOMETRIES ,  true );
    pObject_ShipObj->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_COLLAPSE_BINDINGS ,  true );
    pObject_ShipObj->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_ShipObj->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_MAKE_INDEXED ,  true );
    pObject_ShipObj->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_ORTHONORMALIZATION ,  false );
    pObject_ShipObj->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_PARITY_CHECK ,  true );
    pObject_ShipObj->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_TANGENT_HARD_EDGE_CHECK ,  true );
    pObject_ShipObj->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_OPTIMIZE_SMART_MESHES ,  true );
    pObject_ShipObj->setBuilderNormalMode( vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE );
    pObject_ShipObj->setBuilderTangentMode( vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED );
    pObject_ShipObj->setBuilderTangentGenerationMode( vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED );
    pObject_ShipObj->setBuilderColorTolerance( 0.001000f );
    pObject_ShipObj->setBuilderNormalTolerance( 0.860000f );
    pObject_ShipObj->setGeometryOption( vsNodeLoader::Data::GEOMETRY_OPTION_GENERATE_DISPLAY_LISTS ,  false );
    pObject_ShipObj->setGeometryFormat( vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT ,  0x0FFF );
    pObject_ShipObj->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_FLATTEN ,  true );
    pObject_ShipObj->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_CLEAN ,  true );
    pObject_ShipObj->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_MERGE_GEOMETRIES ,  true );
    pObject_ShipObj->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_BINDINGS ,  true );
    pObject_ShipObj->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_ShipObj->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_VALIDATE ,  false );
    pObject_ShipObj->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_MAKE_INDEXED ,  true );
    pObject_ShipObj->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_SCRUB ,  false );
    pObject_ShipObj->setTextureSubloadEnable( false );
    pObject_ShipObj->setBufferObjectSubloadEnable( true );
    pObject_ShipObj->setTextureSubloadRender( vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED );
    pObject_ShipObj->setTexturePreserveImageLevelsEnable( true );

    s_pInstancesToUnref->push_back( pObject_ShipObj );

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
    pEnv_myEnv->setTimeOfDay( 19.299999f );
    pEnv_myEnv->setTimeMultiplier( 1.000000f );
    pEnv_myEnv->setEphemerisUpdateInterval( 0.000000f );
    pEnv_myEnv->setReferencePosition( -96.790001f ,  32.790001f );
    pEnv_myEnv->setEphemerisTimeZoneOffset( -10000 );
    pEnv_myEnv->setSkyColor( 0.513725f ,  0.701961f ,  0.941176f ,  1.000000f );
    pEnv_myEnv->setVisibilityType( vpEnvFx::VISIBILITY_TYPE_PIXEL_EXP2 );
    pEnv_myEnv->setVisibilityRangeOnset( 0.000000f );
    pEnv_myEnv->setVisibilityRangeOpaque( 60000.000000f );
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
    pEnvCloudLayer_myEnvCloudLayer->setCoverageScale( 0.250000f );
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

    vpMotionUFO* pMotionUFO_myMotionUFO = new vpMotionUFO();
    pMotionUFO_myMotionUFO->setName( "myMotionUFO" );
    pMotionUFO_myMotionUFO->setSpeed( 10 );
    pMotionUFO_myMotionUFO->setBoost( 50 );
    pMotionUFO_myMotionUFO->setBoostTurning( 5 );
    pMotionUFO_myMotionUFO->setRateHeading( 40 );
    pMotionUFO_myMotionUFO->setRatePitch( 20 );

    s_pInstancesToUnref->push_back( pMotionUFO_myMotionUFO );

    vpMarineWaveGeneratorFFT* pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT = new vpMarineWaveGeneratorFFT();
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setName( "myMarineWaveGeneratorFFT" );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setMeshResolution( 128 ,  128 );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setCellExtents( 96.000000f ,  96.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSeaState( 3 );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSurfaceWindSpeed( 8.500000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setDominantWaveDirection( 265.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSignificantWaveHeight( 0.274320f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setPeakThreshold( 0.870000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setTextureAnimationFactor( 0.100000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSuppressSmallWavesFactor( 0.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setAlignmentWithWind( 0.600000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setTravel( 0.400000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setPowerLawDistribution( 2.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setChoppyWavesFactor( 0.249900f );
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

    vpMarineShip* pMarineShip_ShipDef = new vpMarineShip();
    pMarineShip_ShipDef->setName( "ShipDef" );
    pMarineShip_ShipDef->setMaxSpeed( 31.000000f );
    pMarineShip_ShipDef->setBeam( 9.000000f );
    pMarineShip_ShipDef->setWidthAtOrigin( 17.000000f );
    pMarineShip_ShipDef->setMaxTurnRate( 2.000000f );
    pMarineShip_ShipDef->setBowFlareAngle( 16.000000f );
    pMarineShip_ShipDef->setBowOffset( 67.500000f );
    pMarineShip_ShipDef->setBowWidth( 1.000000f );
    pMarineShip_ShipDef->setBowLength( 4.000000f );
    pMarineShip_ShipDef->setBowFreeboard( 3.000000f );
    pMarineShip_ShipDef->setBowStempostAngle( 30.000000f );
    pMarineShip_ShipDef->setBowStempostLength( 15.000000f );
    pMarineShip_ShipDef->setSternOffset( -74.000000f );
    pMarineShip_ShipDef->setSternWidth( 12.500000f );
    pMarineShip_ShipDef->setSternWakeAngle( 7.000000f );
    pMarineShip_ShipDef->setComputeVelocityEnable( true );

    s_pInstancesToUnref->push_back( pMarineShip_ShipDef );

    vpMarineShipMotionStrategy* pMarineShipMotionStrategy_myMarineShipMotionStrategy = new vpMarineShipMotionStrategy();
    pMarineShipMotionStrategy_myMarineShipMotionStrategy->setName( "myMarineShipMotionStrategy" );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy->setComputeYawEnable( true );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy->setSmoothingFactorPortAndStarboard( 140 );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy->setSmoothingFactorBowAndStern( 120 );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy->setPitchFactor( 1.000000f );
    pMarineShipMotionStrategy_myMarineShipMotionStrategy->setRollFactor( 1.000000f );

    s_pInstancesToUnref->push_back( pMarineShipMotionStrategy_myMarineShipMotionStrategy );

    vpMarineFxBowWaveAngled* pMarineFxBowWaveAngled_myMarineFxBowWaveAngled = new vpMarineFxBowWaveAngled();
    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled->setName( "myMarineFxBowWaveAngled" );
    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled->setEnable( true );

    s_pInstancesToUnref->push_back( pMarineFxBowWaveAngled_myMarineFxBowWaveAngled );

    vpMarineFxSternWake* pMarineFxSternWake_myMarineFxSternWake = new vpMarineFxSternWake();
    pMarineFxSternWake_myMarineFxSternWake->setName( "myMarineFxSternWake" );
    pMarineFxSternWake_myMarineFxSternWake->setEnable( true );
    pMarineFxSternWake_myMarineFxSternWake->setDissipationTime( 32.000000f );
    pMarineFxSternWake_myMarineFxSternWake->setTessellationFactor( 1.000000f );
    pMarineFxSternWake_myMarineFxSternWake->setHeightOffset( 0.150000f );

    s_pInstancesToUnref->push_back( pMarineFxSternWake_myMarineFxSternWake );

    vpMarineFxHullWake* pMarineFxHullWake_myMarineFxHullWake = new vpMarineFxHullWake();
    pMarineFxHullWake_myMarineFxHullWake->setName( "myMarineFxHullWake" );
    pMarineFxHullWake_myMarineFxHullWake->setEnable( true );
    pMarineFxHullWake_myMarineFxHullWake->setDissipationTime( 15.000000f );
    pMarineFxHullWake_myMarineFxHullWake->setTessellationFactor( 1.000000f );
    pMarineFxHullWake_myMarineFxHullWake->setHeightOffset( 0.150000f );

    s_pInstancesToUnref->push_back( pMarineFxHullWake_myMarineFxHullWake );



    //
    // Satisfy all references
    //



    pPipeline_myPipeline->addWindow( pWindow_myWindow );

    pWindow_myWindow->addChannel( pChannel_myChannel );


    pObserver_Observer->setStrategy( pMotionUFO_myMotionUFO );
    pObserver_Observer->addChannel( pChannel_myChannel );
    pObserver_Observer->addAttachment( pEnv_myEnv );
    pObserver_Observer->setScene( pScene_myScene );

    pScene_myScene->addChild( pObject_ShipObj );

    pObject_ShipObj->setStrategy( pMarineShipMotionStrategy_myMarineShipMotionStrategy );




    pEnv_myEnv->addEnvFx( pEnvSun_myEnvSun );
    pEnv_myEnv->addEnvFx( pEnvMoon_myEnvMoon );
    pEnv_myEnv->addEnvFx( pEnvSkyDome_myEnvSkyDome );
    pEnv_myEnv->addEnvFx( pEnvCloudLayer_myEnvCloudLayer );
    pEnv_myEnv->addEnvFx( pEnvWind_myEnvWind );








    pMarineOceanObserverCentered_OceanObserverCentered->addObserver( pObserver_Observer );
    pMarineOceanObserverCentered_OceanObserverCentered->setWaveGenerator( pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT );

    pMarineShip_ShipDef->setOcean( pMarineOceanObserverCentered_OceanObserverCentered );
    pMarineShip_ShipDef->setTransform( pObject_ShipObj );

    pMarineShipMotionStrategy_myMarineShipMotionStrategy->setShip( pMarineShip_ShipDef );

    pMarineFxBowWaveAngled_myMarineFxBowWaveAngled->setShip( pMarineShip_ShipDef );

    pMarineFxSternWake_myMarineFxSternWake->setShip( pMarineShip_ShipDef );

    pMarineFxHullWake_myMarineFxHullWake->setShip( pMarineShip_ShipDef );

}




void unconfigure( void )
{
    //
    // Unref all created instances
    //

    s_pInstancesToUnref->clear();
    delete s_pInstancesToUnref;
}

