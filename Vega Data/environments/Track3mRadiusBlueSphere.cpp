//
// This file was automatically generated from C:/Presagis/Suite22/Vega_Prime_22_0/projects/MWEPS/Vega Data/environments/Track3mRadiusBlueSphere.acf
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
#include "vpIsectorHAT.h"
#include "vpRecyclingService.h"
#include "vpApplicationSettings.h"
#include "vpEnvGlobals.h"
#include "vpEnv.h"
#include "vpEnvSun.h"
#include "vpEnvMoon.h"
#include "vpEnvSkyDome.h"
#include "vpEnvCloudLayer2D.h"
#include "vpEnvSnow.h"
#include "vpEnvRain.h"
#include "vpEnvWind.h"
#include "vpMotionUFO.h"
#include "vpOverlay2DImage.h"
#include "vpMarineWaveGeneratorFFT.h"
#include "vpMarineOceanObserverCentered.h"
#include "vpMarineShipAttribute.h"
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
    vpModule::initializeModule( "vpOverlay" );
    vpModule::initializeModule( "vpMarine" );


    //
    // Create all instances
    //

    vpKernel* pKernel_myKernel = vpKernel::instance();
    pKernel_myKernel->setNotifyLevel( vuNotify::LEVEL_NOTICE );
    pKernel_myKernel->setNotifyColorEnable( false );
    pKernel_myKernel->setNotifyShaderErrorEnable( false );
    pKernel_myKernel->setPriority( vuThread::PRIORITY_NORMAL );
    pKernel_myKernel->setProcessorAffinityMask( -1 );
    pKernel_myKernel->setFrameRateLimiterEnable( false );
    pKernel_myKernel->setDesiredFrameRate( 0 );
    pKernel_myKernel->setNotifyClassTypeMode( vuNotify::CLASS_TYPE_MODE_INCLUSIVE );

    vpSearchPath* pSearchPath_mySearchPath = vpSearchPath::instance();
    pSearchPath_mySearchPath->append( "$(PRESAGIS_VEGA_PRIME_22_0)/config/vegaprime/vpenv" );
    pSearchPath_mySearchPath->append( "C:/Presagis/Suite22/Vega_Prime_22_0/config/VegaPrime/vpenv" );
    pSearchPath_mySearchPath->append( "C:/Presagis/Suite22/Vega_Prime_22_0/projects/MWEPS/Vega Data/models" );
    pSearchPath_mySearchPath->append( "C:/Presagis/Suite22/Vega_Prime_22_0/projects/MWEPS/data/models" );

    vpPipeline* pPipeline_myPipeline = new vpPipeline();
    pPipeline_myPipeline->setName( "myPipeline" );
    pPipeline_myPipeline->setMultiThread( vsPipeline::MULTITHREAD_CULL_DRAW );
    pPipeline_myPipeline->setId( 0 );
    pPipeline_myPipeline->setNumCullThreads( 0 );
    pPipeline_myPipeline->setCullThreadPriority( vuThread::PRIORITY_NORMAL );
    pPipeline_myPipeline->setCullThreadProcessorAffinityMask( -1 );
    pPipeline_myPipeline->setDrawThreadPriority( vuThread::PRIORITY_NORMAL );
    pPipeline_myPipeline->setDrawThreadProcessorAffinityMask( -1 );
    pPipeline_myPipeline->setBeginFrameOnVsyncEnable( true );
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
    pPipeline_myPipeline->setGraphicsResourceThreadProcessorAffinityMask( -1 );

    s_pInstancesToUnref->push_back( pPipeline_myPipeline );

    vpWindow* pWindow_myWindow = new vpWindow();
    pWindow_myWindow->setName( "myWindow" );
    pWindow_myWindow->setLabel( "Vega Prime Window" );
    pWindow_myWindow->setOrigin( 825 ,  0 );
    pWindow_myWindow->setSize( 1920 ,  1200 );
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
    pWindow_myWindow->setResizeDesktopEnable( false );

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
    pChannel_myChannel->setSignificantPixelSize( 2 );
    pChannel_myChannel->setCullThreadPriority( vuThread::PRIORITY_NORMAL );
    pChannel_myChannel->setCullThreadProcessorAffinityMask( -1 );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_WIREFRAME ,  false );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_TRANSPARENCY ,  true );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_TEXTURE ,  true );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_LIGHT ,  true );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_FOG ,  true );
    pChannel_myChannel->setGraphicsModeEnable( vpChannel::GRAPHICS_MODE_SHADERS ,  true );
    pChannel_myChannel->setAntiAlias( vsChannel::ANTIALIAS_MULTISAMPLE ,  true );
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
    pObserver_Observer->setTranslate( 0 ,  0 ,  3 );
    pObserver_Observer->setRotate( 0 ,  0 ,  0 );
    pObserver_Observer->setLatencyCriticalEnable( false );

    s_pInstancesToUnref->push_back( pObserver_Observer );

    vpScene* pScene_myScene = new vpScene();
    pScene_myScene->setName( "myScene" );

    s_pInstancesToUnref->push_back( pScene_myScene );

    vpObject* pObject_SphereObject = new vpObject();
    pObject_SphereObject->setName( "SphereObject" );
    pObject_SphereObject->setCullMask( 0x0FFFFFFFF );
    pObject_SphereObject->setRenderMask( 0x0FFFFFFFF );
    pObject_SphereObject->setIsectMask( 0x0FFFFFFFF );
    pObject_SphereObject->setStrategyEnable( true );
    pObject_SphereObject->setTranslate( 0 ,  0 ,  2 );
    pObject_SphereObject->setRotate( 0 ,  0 ,  0 );
    pObject_SphereObject->setScale( 1 ,  1 ,  1 );
    pObject_SphereObject->setStaticEnable( false );
    pObject_SphereObject->setFileName( "3mRadiusSphereBlue.flt" );
    pObject_SphereObject->setAutoPage( vpObject::AUTO_PAGE_SYNCHRONOUS );
    pObject_SphereObject->setManualLODChild( -1 );
    pObject_SphereObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES ,  false );
    pObject_SphereObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE ,  false );
    pObject_SphereObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS ,  true );
    pObject_SphereObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS ,  true );
    pObject_SphereObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES ,  true );
    pObject_SphereObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_COMBINE_LIGHT_POINTS ,  true );
    pObject_SphereObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NAMES ,  true );
    pObject_SphereObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_GENERIC_NODES ,  true );
    pObject_SphereObject->setLoaderDetailMultiTextureStage( -1 );
    pObject_SphereObject->setLoaderBlendTolerance( 0.050000f );
    pObject_SphereObject->setLoaderUnits( vsNodeLoader::Data::LOADER_UNITS_METERS );
    pObject_SphereObject->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_OPTIMIZE_GEOMETRIES ,  true );
    pObject_SphereObject->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_OPTIMIZE_SMART_MESHES ,  true );
    pObject_SphereObject->setBuilderOption( vsNodeLoader::Data::BUILDER_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_SphereObject->setBuilderNormalMode( vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE );
    pObject_SphereObject->setBuilderTangentMode( vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED );
    pObject_SphereObject->setBuilderTangentGenerationMode( vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED );
    pObject_SphereObject->setBuilderColorTolerance( 0.001000f );
    pObject_SphereObject->setBuilderNormalTolerance( 0.860000f );
    pObject_SphereObject->setGeometryFormat( vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT ,  0x01FFFF );
    pObject_SphereObject->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_MERGE_GEOMETRIES ,  true );
    pObject_SphereObject->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_FLATTEN ,  true );
    pObject_SphereObject->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_BINDINGS ,  true );
    pObject_SphereObject->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_SphereObject->setTextureSubloadEnable( true );
    pObject_SphereObject->setBufferObjectSubloadEnable( true );
    pObject_SphereObject->setTextureSubloadRender( vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED );
    pObject_SphereObject->setTexturePreserveImageLevelsEnable( false );

    s_pInstancesToUnref->push_back( pObject_SphereObject );

    vpIsectorHAT* pIsectorHAT_myIsector = new vpIsectorHAT();
    pIsectorHAT_myIsector->setName( "myIsector" );
    pIsectorHAT_myIsector->setEnable( true );
    pIsectorHAT_myIsector->setRenderEnable( false );
    pIsectorHAT_myIsector->setTranslate( 0 ,  0 ,  0 );
    pIsectorHAT_myIsector->setRotate( 0 ,  0 ,  0 );
    pIsectorHAT_myIsector->setMode( 0x02 );
    pIsectorHAT_myIsector->setIsectMask( 0x0FFFFFFFF );
    pIsectorHAT_myIsector->setMaterialMask( 0x0FFFF );
    pIsectorHAT_myIsector->setStrategyEnable( true );
    pIsectorHAT_myIsector->setSegmentZExtent( -5000.000000f ,  5000.000000f );

    s_pInstancesToUnref->push_back( pIsectorHAT_myIsector );

    vpRecyclingService* pRecyclingService_myRecyclingService = vpRecyclingService::instance();
    pRecyclingService_myRecyclingService->setMultiThread( vpRecyclingService::MULTITHREAD_INLINE );
    pRecyclingService_myRecyclingService->setThreadPriority( vuThread::PRIORITY_NORMAL );
    pRecyclingService_myRecyclingService->setThreadProcessorAffinityMask( -1 );
    pRecyclingService_myRecyclingService->setRecycleTime( -1 );

    vpApplicationSettings* pApplicationSettings_myApplicationSettings = vpApplicationSettings::instance();
    pApplicationSettings_myApplicationSettings->setMode( vrShaderInfrastructure::MODE_REPLACE_SHADERS );
    pApplicationSettings_myApplicationSettings->setLightPointMinimumSizeOverride( 2.000000f );
    pApplicationSettings_myApplicationSettings->setDeferredRenderingEnabled( false );
    pApplicationSettings_myApplicationSettings->setFXAAQualityPreset( vpApplicationSettings::FXAA_DEFAULT );
    pApplicationSettings_myApplicationSettings->setDecalFactorScale( 1.000000f );
    pApplicationSettings_myApplicationSettings->setDecalUnitsScale( 1.000000f );
    pApplicationSettings_myApplicationSettings->setPointBillboardUnitsScale( 1.000000f );
    pApplicationSettings_myApplicationSettings->setLogZBufferEnable( false );
    pApplicationSettings_myApplicationSettings->setBackwardsCompatibleContextEnable( true );

    vpEnvGlobals* pEnvGlobals_myEnvGlobals = vpEnvGlobals::instance();
    pEnvGlobals_myEnvGlobals->addFogMaximumAltitude( 0.100000f ,  300.000000f );
    pEnvGlobals_myEnvGlobals->addFogMaximumAltitude( 0.250000f ,  1200.000000f );
    pEnvGlobals_myEnvGlobals->addFogMaximumAltitude( 0.400000f ,  2000.000000f );
    pEnvGlobals_myEnvGlobals->setEnvironmentMapGenerationEnable( false );

    vpEnv* pEnv_myEnv = new vpEnv();
    pEnv_myEnv->setName( "myEnv" );
    pEnv_myEnv->setDate( 6 ,  11 ,  2012 );
    pEnv_myEnv->setTimeOfDay( 11.670000f );
    pEnv_myEnv->setTimeMultiplier( 1.000000f );
    pEnv_myEnv->setEphemerisUpdateInterval( 0.000000f );
    pEnv_myEnv->setReferencePosition( -80.183998f ,  28.523001f );
    pEnv_myEnv->setEphemerisTimeZoneOffset( -10000 );
    pEnv_myEnv->setVisibilityRangeOpaque( 20000.000000f );
    pEnv_myEnv->setVisibilityColor( 0.764706f ,  0.858824f ,  1.000000f ,  1.000000f );
    pEnv_myEnv->setHazeColor( 0.772549f ,  0.772549f ,  0.772549f ,  0.445397f );
    pEnv_myEnv->setManageVisibilityColorsEnable( true );
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
    pEnvSun_myEnvSun->setGeometryEnable( true );

    s_pInstancesToUnref->push_back( pEnvSun_myEnvSun );

    vpEnvMoon* pEnvMoon_myEnvMoon = new vpEnvMoon();
    pEnvMoon_myEnvMoon->setName( "myEnvMoon" );
    pEnvMoon_myEnvMoon->setEnable( true );
    pEnvMoon_myEnvMoon->setGeometryEnable( true );
    pEnvMoon_myEnvMoon->setTextureFile( "moon.png" );
    pEnvMoon_myEnvMoon->setTextureBlendColor( 1.000000f ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnvMoon_myEnvMoon->setTextureBlendMode( vpEnvMoon::TEXTURE_BLEND_MODE_MODULATE );
    pEnvMoon_myEnvMoon->setColor( 0.811765f ,  0.886275f ,  0.937255f ,  1.000000f );
    pEnvMoon_myEnvMoon->setVisibilityRangeRatio( 0.200000f );
    pEnvMoon_myEnvMoon->setAngularSize( 1.500000f );
    pEnvMoon_myEnvMoon->setHorizonAngle( 30.000000f );
    pEnvMoon_myEnvMoon->setHorizonSizeScale( 1.700000f );

    s_pInstancesToUnref->push_back( pEnvMoon_myEnvMoon );

    vpEnvSkyDome* pEnvSkyDome_myEnvSkyDome = new vpEnvSkyDome();
    pEnvSkyDome_myEnvSkyDome->setName( "myEnvSkyDome" );
    pEnvSkyDome_myEnvSkyDome->setEnable( true );
    pEnvSkyDome_myEnvSkyDome->setColorGradientFactor( 1.000000f );

    s_pInstancesToUnref->push_back( pEnvSkyDome_myEnvSkyDome );

    vpEnvCloudLayer2D* pEnvCloudLayer2D_myEnvCloudLayer = new vpEnvCloudLayer2D();
    pEnvCloudLayer2D_myEnvCloudLayer->setName( "myEnvCloudLayer" );
    pEnvCloudLayer2D_myEnvCloudLayer->setEnable( true );
    pEnvCloudLayer2D_myEnvCloudLayer->setColor( 0.300000f ,  0.300000f ,  0.300000f ,  1.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setElevation( 2000.000000f ,  5437.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setCoverageScale( 0.140000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setGeometryEnable( true );
    pEnvCloudLayer2D_myEnvCloudLayer->setEnvHazeColorScale( 0.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setTransitionRange( 500.000000f ,  500.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setScudEnable( false );
    pEnvCloudLayer2D_myEnvCloudLayer->setTextureFile( "cloud_scattered.png" );
    pEnvCloudLayer2D_myEnvCloudLayer->setTextureTiling( 3.000000f ,  3.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setShadowsEnable( true );
    pEnvCloudLayer2D_myEnvCloudLayer->setShadowIntensity( 0.610000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setShadowsContribution( 0.100000f ,  0.900000f );

    s_pInstancesToUnref->push_back( pEnvCloudLayer2D_myEnvCloudLayer );

    vpEnvSnow* pEnvSnow_myEnvSnow = new vpEnvSnow();
    pEnvSnow_myEnvSnow->setName( "myEnvSnow" );
    pEnvSnow_myEnvSnow->setEnable( false );
    pEnvSnow_myEnvSnow->setColor( 1.000000f ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnvSnow_myEnvSnow->setTextureBlendColor( 1.000000f ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnvSnow_myEnvSnow->setTextureBlendMode( vpEnvPrecipitation::TEXTURE_BLEND_MODE_MODULATE );
    pEnvSnow_myEnvSnow->setTextureFile( "" );
    pEnvSnow_myEnvSnow->setNumParticles( 50000 );
    pEnvSnow_myEnvSnow->setEmitterBoxSize( 10 );
    pEnvSnow_myEnvSnow->setInternalClipBoxEnable( false );
    pEnvSnow_myEnvSnow->setInternalClipBoxSize( 2 );
    pEnvSnow_myEnvSnow->setParticleSize( 0.010000f );
    pEnvSnow_myEnvSnow->setGravitationalConstant( -1 );
    pEnvSnow_myEnvSnow->setVelocityScale( -1.000000f );

    s_pInstancesToUnref->push_back( pEnvSnow_myEnvSnow );

    vpEnvRain* pEnvRain_myEnvRain = new vpEnvRain();
    pEnvRain_myEnvRain->setName( "myEnvRain" );
    pEnvRain_myEnvRain->setEnable( false );
    pEnvRain_myEnvRain->setColor( 1.000000f ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnvRain_myEnvRain->setTextureBlendColor( 1.000000f ,  1.000000f ,  1.000000f ,  1.000000f );
    pEnvRain_myEnvRain->setTextureBlendMode( vpEnvPrecipitation::TEXTURE_BLEND_MODE_MODULATE );
    pEnvRain_myEnvRain->setTextureFile( "" );
    pEnvRain_myEnvRain->setNumParticles( 5000 );
    pEnvRain_myEnvRain->setEmitterBoxSize( 28 );
    pEnvRain_myEnvRain->setInternalClipBoxEnable( false );
    pEnvRain_myEnvRain->setInternalClipBoxSize( 0 );
    pEnvRain_myEnvRain->setParticleSize( 0.010000f );
    pEnvRain_myEnvRain->setGravitationalConstant( -2 );
    pEnvRain_myEnvRain->setVelocityScale( 9.000000f );

    s_pInstancesToUnref->push_back( pEnvRain_myEnvRain );

    vpEnvWind* pEnvWind_myEnvWind = new vpEnvWind();
    pEnvWind_myEnvWind->setName( "myEnvWind" );
    pEnvWind_myEnvWind->setEnable( true );
    pEnvWind_myEnvWind->setSpeed( 0.000000f );
    pEnvWind_myEnvWind->setDirection( 0.000000f ,  1.000000f ,  0.000000f );

    s_pInstancesToUnref->push_back( pEnvWind_myEnvWind );

    vpMotionUFO* pMotionUFO_myMotionUFO = new vpMotionUFO();
    pMotionUFO_myMotionUFO->setName( "myMotionUFO" );
    pMotionUFO_myMotionUFO->setSpeed( 0 );
    pMotionUFO_myMotionUFO->setBoost( 50 );
    pMotionUFO_myMotionUFO->setBoostTurning( 5 );
    pMotionUFO_myMotionUFO->setRateHeading( 0 );
    pMotionUFO_myMotionUFO->setRatePitch( 0 );

    s_pInstancesToUnref->push_back( pMotionUFO_myMotionUFO );

    vpOverlay2DImage* pOverlay2DImage_SMBCrosshair = new vpOverlay2DImage();
    pOverlay2DImage_SMBCrosshair->setName( "SMBCrosshair" );
    pOverlay2DImage_SMBCrosshair->setEnable( true );
    pOverlay2DImage_SMBCrosshair->addImageFile( "RedBlueAim.png" );
    pOverlay2DImage_SMBCrosshair->setDisplayTime( 5000 );
    pOverlay2DImage_SMBCrosshair->setOrigin( 0.185000f ,  0.155000f );
    pOverlay2DImage_SMBCrosshair->setScale( 0.030000f ,  0.050000f );
    pOverlay2DImage_SMBCrosshair->setFadeInDuration( 0 );
    pOverlay2DImage_SMBCrosshair->setFadeOutDuration( 0 );
    pOverlay2DImage_SMBCrosshair->setBlinkingEnable( false );
    pOverlay2DImage_SMBCrosshair->setRenderingPriority( 100 );

    s_pInstancesToUnref->push_back( pOverlay2DImage_SMBCrosshair );

    vpMarineWaveGeneratorFFT* pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT = new vpMarineWaveGeneratorFFT();
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setName( "myMarineWaveGeneratorFFT" );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setMeshResolution( 64 ,  64 );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setCellExtents( 96.000000f ,  96.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setWaveSpectrumModel( vpMarineWaveGeneratorFFT::SPECTRUM_MODEL_PHILIPS );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSeaState( 4 );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSurfaceWindSpeed( 15.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setDominantWaveDirection( 229.000000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSignificantWaveHeight( 1.219200f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setPeakThreshold( 0.940000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setTextureAnimationFactor( 0.440000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSuppressSmallWavesFactor( 0.480000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setAlignmentWithWind( 0.510000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setTravel( 0.730000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setPowerLawDistribution( 2.030000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setChoppyWavesFactor( 0.570000f );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setNormalCalculationsEnable( true );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setFreezeEnable( false );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setGpuEnable( false );
    pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT->setSeaStateTransitionTime( 0.000000f );

    s_pInstancesToUnref->push_back( pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT );

    vpMarineOceanObserverCentered* pMarineOceanObserverCentered_OceanObserverCentered = new vpMarineOceanObserverCentered();
    pMarineOceanObserverCentered_OceanObserverCentered->setName( "OceanObserverCentered" );
    pMarineOceanObserverCentered_OceanObserverCentered->setEnable( true );
    pMarineOceanObserverCentered_OceanObserverCentered->setTranslate( 0 ,  0 ,  0 );
    pMarineOceanObserverCentered_OceanObserverCentered->setTideHeight( 0.000000f );
    pMarineOceanObserverCentered_OceanObserverCentered->setAutoTextureSeaStateEnable( false );
    pMarineOceanObserverCentered_OceanObserverCentered->setLeanAndMeanEnable( false );
    pMarineOceanObserverCentered_OceanObserverCentered->setOverallColor( 0.078000f ,  0.138000f ,  0.190000f ,  1.000000f );
    pMarineOceanObserverCentered_OceanObserverCentered->addLODSwitchDistance( 300 );
    pMarineOceanObserverCentered_OceanObserverCentered->addLODSwitchDistance( 600 );
    pMarineOceanObserverCentered_OceanObserverCentered->addLODSwitchDistance( 900 );
    pMarineOceanObserverCentered_OceanObserverCentered->addLODSwitchDistance( 1200 );
    pMarineOceanObserverCentered_OceanObserverCentered->setFarClipPlane( 2500 );
    pMarineOceanObserverCentered_OceanObserverCentered->setEnvironmentMapTextureFile( "" );
    pMarineOceanObserverCentered_OceanObserverCentered->setLocalReflectionsEnable( true );
    pMarineOceanObserverCentered_OceanObserverCentered->setLocalReflectionsRipplingStrength( 0.790000f );
    pMarineOceanObserverCentered_OceanObserverCentered->setReflectionStrength( 100.000000f );
    pMarineOceanObserverCentered_OceanObserverCentered->setReflectionSharpness( true );
    pMarineOceanObserverCentered_OceanObserverCentered->setGlintStrength( 0.000000f );
    pMarineOceanObserverCentered_OceanObserverCentered->setRangeScale( 1.000000f );
    pMarineOceanObserverCentered_OceanObserverCentered->setCullMask( 0x0FFFFFFFF );
    pMarineOceanObserverCentered_OceanObserverCentered->setRenderMask( 0x0FFFFFFFF );
    pMarineOceanObserverCentered_OceanObserverCentered->setIsectMask( 0x0FFFFFFFF );

    s_pInstancesToUnref->push_back( pMarineOceanObserverCentered_OceanObserverCentered );

    vpMarineShipAttribute* pMarineShipAttribute_SphereMarineShip = new vpMarineShipAttribute();
    pMarineShipAttribute_SphereMarineShip->setName( "SphereMarineShip" );
    pMarineShipAttribute_SphereMarineShip->setPriority( 1 );
    pMarineShipAttribute_SphereMarineShip->setMaxSpeed( 100.000000f );
    pMarineShipAttribute_SphereMarineShip->setBeam( 1.000000f );
    pMarineShipAttribute_SphereMarineShip->setWidthAtOrigin( 1.000000f );
    pMarineShipAttribute_SphereMarineShip->setMaxTurnRate( 2.000000f );
    pMarineShipAttribute_SphereMarineShip->setBowFlareAngle( 30.840000f );
    pMarineShipAttribute_SphereMarineShip->setBowOffset( 7.000000f );
    pMarineShipAttribute_SphereMarineShip->setBowWidth( 1.000000f );
    pMarineShipAttribute_SphereMarineShip->setBowLength( 1.000000f );
    pMarineShipAttribute_SphereMarineShip->setBowFreeboard( 2.000000f );
    pMarineShipAttribute_SphereMarineShip->setBowStempostAngle( 30.000000f );
    pMarineShipAttribute_SphereMarineShip->setBowStempostLength( 1.000000f );
    pMarineShipAttribute_SphereMarineShip->setSternOffset( -7.000000f );
    pMarineShipAttribute_SphereMarineShip->setSternWidth( 2.000000f );
    pMarineShipAttribute_SphereMarineShip->setSternWakeAngle( 6.000000f );
    pMarineShipAttribute_SphereMarineShip->setWakeIntensityScale( 1.000000f );
    pMarineShipAttribute_SphereMarineShip->setComputeVelocityEnable( true );
    pMarineShipAttribute_SphereMarineShip->setWaveDampingEnable( false );
    pMarineShipAttribute_SphereMarineShip->setWaveDampingScale( 0.333000f );
    pMarineShipAttribute_SphereMarineShip->setWaveDampingMaxSpeed( 8.000000f );
    pMarineShipAttribute_SphereMarineShip->setWaveDampingDownwindScale( 1.000000f );
    pMarineShipAttribute_SphereMarineShip->setWaveDampingWidthScale( 0.500000f );
    pMarineShipAttribute_SphereMarineShip->setMass( 3000.000000f );

    s_pInstancesToUnref->push_back( pMarineShipAttribute_SphereMarineShip );

    vpMarineShipMotionStrategy* pMarineShipMotionStrategy_SphereMarineShipMotionStrategy = new vpMarineShipMotionStrategy();
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setName( "SphereMarineShipMotionStrategy" );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setMotionModel( vpMarineShipMotionStrategy::MODEL_DEFAULT );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setComputeYawEnable( true );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setSmoothingFactorPortAndStarboard( 50 );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setSmoothingFactorBowAndStern( 90 );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setPitchFactor( 1.000000f );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setRollFactor( 1.000000f );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setHeelFactor( 0.000000f );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setTrim( 0.000000f );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setDraft( 0.000000f );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setHeel( 0.000000f );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setDampingConstant( 1 ,  1 ,  1 );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setAngularDampingConstant( 0.4 ,  1 ,  1 );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setSpringConstant( 0 ,  0 ,  6000 );
    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setAngularSpringConstant( 1 ,  3000 ,  3000 );

    s_pInstancesToUnref->push_back( pMarineShipMotionStrategy_SphereMarineShipMotionStrategy );

    vpMarineFxBowWaveAngled* pMarineFxBowWaveAngled_SphereMarineFxBowWaveAngled = new vpMarineFxBowWaveAngled();
    pMarineFxBowWaveAngled_SphereMarineFxBowWaveAngled->setName( "SphereMarineFxBowWaveAngled" );
    pMarineFxBowWaveAngled_SphereMarineFxBowWaveAngled->setEnable( true );

    s_pInstancesToUnref->push_back( pMarineFxBowWaveAngled_SphereMarineFxBowWaveAngled );

    vpMarineFxSternWake* pMarineFxSternWake_SphereMarineFxSternWake = new vpMarineFxSternWake();
    pMarineFxSternWake_SphereMarineFxSternWake->setName( "SphereMarineFxSternWake" );
    pMarineFxSternWake_SphereMarineFxSternWake->setEnable( true );
    pMarineFxSternWake_SphereMarineFxSternWake->setDissipationTime( 30.000000f );
    pMarineFxSternWake_SphereMarineFxSternWake->setTessellationFactor( 1.000000f );
    pMarineFxSternWake_SphereMarineFxSternWake->setHeightOffset( 0.150000f );

    s_pInstancesToUnref->push_back( pMarineFxSternWake_SphereMarineFxSternWake );

    vpMarineFxHullWake* pMarineFxHullWake_SphereMarineFxHullWake = new vpMarineFxHullWake();
    pMarineFxHullWake_SphereMarineFxHullWake->setName( "SphereMarineFxHullWake" );
    pMarineFxHullWake_SphereMarineFxHullWake->setEnable( true );
    pMarineFxHullWake_SphereMarineFxHullWake->setDissipationTime( 30.000000f );
    pMarineFxHullWake_SphereMarineFxHullWake->setTessellationFactor( 1.000000f );
    pMarineFxHullWake_SphereMarineFxHullWake->setHeightOffset( 0.150000f );

    s_pInstancesToUnref->push_back( pMarineFxHullWake_SphereMarineFxHullWake );



    //
    // Satisfy all references
    //



    pPipeline_myPipeline->addWindow( pWindow_myWindow );

    pWindow_myWindow->addChannel( pChannel_myChannel );


    pObserver_Observer->setStrategy( pMotionUFO_myMotionUFO );
    pObserver_Observer->addChannel( pChannel_myChannel );
    pObserver_Observer->addAttachment( pEnv_myEnv );
    pObserver_Observer->setScene( pScene_myScene );

    pScene_myScene->addChild( pObject_SphereObject );

    pObject_SphereObject->addChild( pMarineFxBowWaveAngled_SphereMarineFxBowWaveAngled );
    pObject_SphereObject->addChild( pMarineFxSternWake_SphereMarineFxSternWake );
    pObject_SphereObject->addChild( pMarineFxHullWake_SphereMarineFxHullWake );
    pObject_SphereObject->addAttribute( pMarineShipAttribute_SphereMarineShip );





    pEnv_myEnv->addEnvFx( pEnvSun_myEnvSun );
    pEnv_myEnv->addEnvFx( pEnvMoon_myEnvMoon );
    pEnv_myEnv->addEnvFx( pEnvSkyDome_myEnvSkyDome );
    pEnv_myEnv->addEnvFx( pEnvCloudLayer2D_myEnvCloudLayer );
    pEnv_myEnv->addEnvFx( pEnvWind_myEnvWind );
    pEnv_myEnv->addEnvFx( pEnvRain_myEnvRain );
    pEnv_myEnv->addEnvFx( pEnvSnow_myEnvSnow );











    pMarineOceanObserverCentered_OceanObserverCentered->addObserver( pObserver_Observer );
    pMarineOceanObserverCentered_OceanObserverCentered->setWaveGenerator( pMarineWaveGeneratorFFT_myMarineWaveGeneratorFFT );

    pMarineShipAttribute_SphereMarineShip->setOcean( pMarineOceanObserverCentered_OceanObserverCentered );

    pMarineShipMotionStrategy_SphereMarineShipMotionStrategy->setShip( pMarineShipAttribute_SphereMarineShip );

    pMarineFxBowWaveAngled_SphereMarineFxBowWaveAngled->setShip( pMarineShipAttribute_SphereMarineShip );

    pMarineFxSternWake_SphereMarineFxSternWake->setShip( pMarineShipAttribute_SphereMarineShip );

    pMarineFxHullWake_SphereMarineFxHullWake->setShip( pMarineShipAttribute_SphereMarineShip );

}




void unconfigure( void )
{
    //
    // Unref all created instances
    //

    s_pInstancesToUnref->clear();
    delete s_pInstancesToUnref;
}

