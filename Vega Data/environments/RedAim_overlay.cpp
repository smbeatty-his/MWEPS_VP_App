//
// This file was automatically generated from C:/Presagis/Suite22/Vega_Prime_22_0/projects/MWEPS/Vega Data/environments/RedAim_overlay.acf
//
#include "vpModule.h"
#include "vpKernel.h"
#include "vpPagingMgr.h"
#include "vpSearchPath.h"
#include "vpPipeline.h"
#include "vpWindow.h"
#include "vpChannel.h"
#include "vpObserver.h"
#include "vpScene.h"
#include "vpObject.h"
#include "vpRecyclingService.h"
#include "vpApplicationSettings.h"
#include "vpEnvGlobals.h"
#include "vpEnv.h"
#include "vpEnvSun.h"
#include "vpEnvMoon.h"
#include "vpEnvSkyDome.h"
#include "vpEnvCloudLayer2D.h"
#include "vpEnvStars.h"
#include "vpEnvWind.h"
#include "vpMotionUFO.h"
#include "vpOverlay2DImage.h"
#include "vpApp.h"

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


    //
    // Create all instances
    //

    vpKernel* pKernel_myKernel = vpKernel::instance();
    pKernel_myKernel->setNotifyLevel( vuNotify::LEVEL_WARN );
    pKernel_myKernel->setNotifyColorEnable( false );
    pKernel_myKernel->setNotifyShaderErrorEnable( false );
    pKernel_myKernel->setPriority( vuThread::PRIORITY_NORMAL );
    pKernel_myKernel->setProcessorAffinityMask( -1 );
    pKernel_myKernel->setFrameRateLimiterEnable( true );
    pKernel_myKernel->setDesiredFrameRate( 0 );
    pKernel_myKernel->setNotifyClassTypeMode( vuNotify::CLASS_TYPE_MODE_INCLUSIVE );

    vpPagingMgr* pPagingMgr_myPagingMgr = vpPagingMgr::instance();
    pPagingMgr_myPagingMgr->setAsynchronousPagingQueueEnable( true );
    pPagingMgr_myPagingMgr->setAsynchronousFileIOEnable( false );
    pPagingMgr_myPagingMgr->setDefaultQueuePriority( vuThread::PRIORITY_NORMAL );
    pPagingMgr_myPagingMgr->setDefaultQueueProcessorAffinityMask( -1 );
    pPagingMgr_myPagingMgr->setMaxNumPageablesToBeCompletedPerFrame( -1 );

    vpSearchPath* pSearchPath_mySearchPath = vpSearchPath::instance();
    pSearchPath_mySearchPath->append( "$(PRESAGIS_VEGA_PRIME_RESOURCE_22_0)/resources/data/databases/camp_pendleton/" );
    pSearchPath_mySearchPath->append( "." );
    pSearchPath_mySearchPath->append( "C:/Users/MWEPS/Desktop" );
    pSearchPath_mySearchPath->append( "C:/Presagis/Suite22/Vega_Prime_22_0/projects/MWEPS" );

    vpPipeline* pPipeline_myPipeline = new vpPipeline();
    pPipeline_myPipeline->setName( "myPipeline" );
    pPipeline_myPipeline->setMultiThread( vsPipeline::MULTITHREAD_INLINE );
    pPipeline_myPipeline->setId( 0 );
    pPipeline_myPipeline->setNumCullThreads( 0 );
    pPipeline_myPipeline->setCullThreadPriority( vuThread::PRIORITY_NORMAL );
    pPipeline_myPipeline->setCullThreadProcessorAffinityMask( -1 );
    pPipeline_myPipeline->setDrawThreadPriority( vuThread::PRIORITY_NORMAL );
    pPipeline_myPipeline->setDrawThreadProcessorAffinityMask( -1 );
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
    pPipeline_myPipeline->setGraphicsResourceThreadProcessorAffinityMask( -1 );

    s_pInstancesToUnref->push_back( pPipeline_myPipeline );

    vpWindow* pWindow_myWindow = new vpWindow();
    pWindow_myWindow->setName( "myWindow" );
    pWindow_myWindow->setLabel( "Vega Prime Window" );
    pWindow_myWindow->setOrigin( 0 ,  0 );
    pWindow_myWindow->setSize( 1024 ,  768 );
    pWindow_myWindow->setFullScreenEnable( false );
    pWindow_myWindow->setBorderEnable( true );
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
    pChannel_myChannel->setFOVSymmetric( 45.000000f ,  -1.000000f );
    pChannel_myChannel->setNearFar( 1.000000f ,  110000.000000f );
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
    pChannel_myChannel->setAntiAlias( vsChannel::ANTIALIAS_MULTISAMPLE ,  false );
    pChannel_myChannel->setStatisticsPage( vpChannel::PAGE_OFF );
    pChannel_myChannel->setCullBoundingBoxTestEnable( false );
    pChannel_myChannel->setOpaqueSort( vpChannel::OPAQUE_SORT_TEXTURE ,  vpChannel::OPAQUE_SORT_MATERIAL );
    pChannel_myChannel->setTransparentSort( vpChannel::TRANSPARENT_SORT_DEPTH );
    pChannel_myChannel->setDrawBuffer( vpChannel::DRAW_BUFFER_DEFAULT );
    pChannel_myChannel->setStressEnable( false );
    pChannel_myChannel->setStressParameters( 1 ,  20 ,  0.75 ,  0.5 ,  2 );

    s_pInstancesToUnref->push_back( pChannel_myChannel );

    vpObserver* pObserver_myObserver = new vpObserver();
    pObserver_myObserver->setName( "myObserver" );
    pObserver_myObserver->setStrategyEnable( true );
    pObserver_myObserver->setTranslate( -1297.13 ,  -1025.92 ,  343.347 );
    pObserver_myObserver->setRotate( 292 ,  -7 ,  0 );
    pObserver_myObserver->setLatencyCriticalEnable( false );

    s_pInstancesToUnref->push_back( pObserver_myObserver );

    vpScene* pScene_myScene = new vpScene();
    pScene_myScene->setName( "myScene" );

    s_pInstancesToUnref->push_back( pScene_myScene );

    vpObject* pObject_myObject = new vpObject();
    pObject_myObject->setName( "myObject" );
    pObject_myObject->setCullMask( 0x0FFFFFFFF );
    pObject_myObject->setRenderMask( 0x0FFFFFFFF );
    pObject_myObject->setIsectMask( 0x0FFFFFFFF );
    pObject_myObject->setStrategyEnable( false );
    pObject_myObject->setTranslate( 0 ,  0 ,  0 );
    pObject_myObject->setRotate( 0 ,  0 ,  0 );
    pObject_myObject->setScale( 1 ,  1 ,  1 );
    pObject_myObject->setStaticEnable( false );
    pObject_myObject->setFileName( "camp_pendleton.flt" );
    pObject_myObject->setAutoPage( vpObject::AUTO_PAGE_SYNCHRONOUS );
    pObject_myObject->setManualLODChild( -1 );
    pObject_myObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES ,  false );
    pObject_myObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE ,  false );
    pObject_myObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS ,  true );
    pObject_myObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS ,  true );
    pObject_myObject->setLoaderOption( vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES ,  true );
    pObject_myObject->setLoaderDetailMultiTextureStage( -1 );
    pObject_myObject->setLoaderBlendTolerance( 0.050000f );
    pObject_myObject->setLoaderUnits( vsNodeLoader::Data::LOADER_UNITS_METERS );
    pObject_myObject->setBuilderNormalMode( vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE );
    pObject_myObject->setBuilderTangentMode( vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED );
    pObject_myObject->setBuilderTangentGenerationMode( vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED );
    pObject_myObject->setBuilderColorTolerance( 0.001000f );
    pObject_myObject->setBuilderNormalTolerance( 0.860000f );
    pObject_myObject->setGeometryFormat( vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT ,  0x01FFFF );
    pObject_myObject->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_BINDINGS ,  true );
    pObject_myObject->setPostLoadOption( vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_TRIANGLE_STRIPS ,  true );
    pObject_myObject->setTextureSubloadEnable( true );
    pObject_myObject->setBufferObjectSubloadEnable( true );
    pObject_myObject->setTextureSubloadRender( vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED );
    pObject_myObject->setTexturePreserveImageLevelsEnable( true );

    s_pInstancesToUnref->push_back( pObject_myObject );

    vpRecyclingService* pRecyclingService_myRecyclingService = vpRecyclingService::instance();
    pRecyclingService_myRecyclingService->setMultiThread( vpRecyclingService::MULTITHREAD_INLINE );
    pRecyclingService_myRecyclingService->setThreadPriority( vuThread::PRIORITY_NORMAL );
    pRecyclingService_myRecyclingService->setThreadProcessorAffinityMask( -1 );
    pRecyclingService_myRecyclingService->setRecycleTime( -1 );

    vpApplicationSettings* pApplicationSettings_myApplicationSettings = vpApplicationSettings::instance();
    pApplicationSettings_myApplicationSettings->setMode( vrShaderInfrastructure::MODE_REPLACE_SHADERS );
    pApplicationSettings_myApplicationSettings->setLightPointMinimumSizeOverride( 2.000000f );
    pApplicationSettings_myApplicationSettings->setLightPointBypassSoftClip( false );
    pApplicationSettings_myApplicationSettings->setDeferredRenderingEnabled( false );
    pApplicationSettings_myApplicationSettings->setFXAAQualityPreset( vpApplicationSettings::FXAA_DEFAULT );
    pApplicationSettings_myApplicationSettings->setDecalFactorScale( 1.000000f );
    pApplicationSettings_myApplicationSettings->setDecalUnitsScale( 1.000000f );
    pApplicationSettings_myApplicationSettings->setPointBillboardUnitsScale( 1.000000f );
    pApplicationSettings_myApplicationSettings->setMaxDecalDerivativeValue( 10.000000f );
    pApplicationSettings_myApplicationSettings->setLogZBufferEnable( false );
    pApplicationSettings_myApplicationSettings->setBackwardsCompatibleContextEnable( true );

    vpEnvGlobals* pEnvGlobals_myEnvGlobals = vpEnvGlobals::instance();
    pEnvGlobals_myEnvGlobals->addFogMaximumAltitude( 0.100000f ,  300.000000f );
    pEnvGlobals_myEnvGlobals->addFogMaximumAltitude( 0.250000f ,  1200.000000f );
    pEnvGlobals_myEnvGlobals->addFogMaximumAltitude( 0.400000f ,  2000.000000f );
    pEnvGlobals_myEnvGlobals->setEnvironmentMapGenerationEnable( false );

    vpEnv* pEnv_myEnv = new vpEnv();
    pEnv_myEnv->setName( "myEnv" );
    pEnv_myEnv->setDate( 1 ,  9 ,  2006 );
    pEnv_myEnv->setTimeOfDay( 9.250000f );
    pEnv_myEnv->setTimeMultiplier( 1.000000f );
    pEnv_myEnv->setEphemerisUpdateInterval( 0.000000f );
    pEnv_myEnv->setReferencePosition( -117.355103f ,  33.301300f );
    pEnv_myEnv->setEphemerisTimeZoneOffset( -10000 );
    pEnv_myEnv->setVisibilityRangeOpaque( 60000.000000f );
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
    pEnvMoon_myEnvMoon->setVisibilityRangeRatio( 0.100000f );
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
    pEnvCloudLayer2D_myEnvCloudLayer->setElevation( 5000.000000f ,  6000.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setCoverageScale( 0.250000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setGeometryEnable( true );
    pEnvCloudLayer2D_myEnvCloudLayer->setEnvHazeColorScale( 0.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setTransitionRange( 500.000000f ,  500.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setScudEnable( false );
    pEnvCloudLayer2D_myEnvCloudLayer->setTextureFile( "" );
    pEnvCloudLayer2D_myEnvCloudLayer->setTextureTiling( 2.000000f ,  2.000000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setShadowsEnable( false );
    pEnvCloudLayer2D_myEnvCloudLayer->setShadowIntensity( 0.600000f );
    pEnvCloudLayer2D_myEnvCloudLayer->setShadowsContribution( 0.100000f ,  0.900000f );

    s_pInstancesToUnref->push_back( pEnvCloudLayer2D_myEnvCloudLayer );

    vpEnvStars* pEnvStars_myEnvStars = new vpEnvStars();
    pEnvStars_myEnvStars->setName( "myEnvStars" );
    pEnvStars_myEnvStars->setEnable( true );
    pEnvStars_myEnvStars->setIntensityThreshold( 0.350000f );
    pEnvStars_myEnvStars->setBrightnessThreshold( 0.400000f ,  0.250000f );
    pEnvStars_myEnvStars->setVisibilityRangeRatio( 0.100000f );
    pEnvStars_myEnvStars->setPointSize( 2.300000f );

    s_pInstancesToUnref->push_back( pEnvStars_myEnvStars );

    vpEnvWind* pEnvWind_myEnvWind = new vpEnvWind();
    pEnvWind_myEnvWind->setName( "myEnvWind" );
    pEnvWind_myEnvWind->setEnable( true );
    pEnvWind_myEnvWind->setSpeed( 100.000000f );
    pEnvWind_myEnvWind->setDirection( 0.000000f ,  1.000000f ,  0.000000f );

    s_pInstancesToUnref->push_back( pEnvWind_myEnvWind );

    vpMotionUFO* pMotionUFO_myMotion = new vpMotionUFO();
    pMotionUFO_myMotion->setName( "myMotion" );
    pMotionUFO_myMotion->setSpeed( 10 );
    pMotionUFO_myMotion->setBoost( 50 );
    pMotionUFO_myMotion->setBoostTurning( 5 );
    pMotionUFO_myMotion->setRateHeading( 40 );
    pMotionUFO_myMotion->setRatePitch( 20 );

    s_pInstancesToUnref->push_back( pMotionUFO_myMotion );

    vpOverlay2DImage* pOverlay2DImage_myOverlay2DImage = new vpOverlay2DImage();
    pOverlay2DImage_myOverlay2DImage->setName( "myOverlay2DImage" );
    pOverlay2DImage_myOverlay2DImage->setEnable( true );
    pOverlay2DImage_myOverlay2DImage->addImageFile( "RedAim.png" );
    pOverlay2DImage_myOverlay2DImage->setDisplayTime( 5000 );
    pOverlay2DImage_myOverlay2DImage->setOrigin( 0.185000f ,  0.155000f );
    pOverlay2DImage_myOverlay2DImage->setScale( 0.460000f ,  0.440000f );
    pOverlay2DImage_myOverlay2DImage->setFadeInDuration( 0 );
    pOverlay2DImage_myOverlay2DImage->setFadeOutDuration( 0 );
    pOverlay2DImage_myOverlay2DImage->setBlinkingEnable( false );
    pOverlay2DImage_myOverlay2DImage->setRenderingPriority( 100 );

    s_pInstancesToUnref->push_back( pOverlay2DImage_myOverlay2DImage );



    //
    // Satisfy all references
    //




    pPipeline_myPipeline->addWindow( pWindow_myWindow );

    pWindow_myWindow->addChannel( pChannel_myChannel );


    pObserver_myObserver->setStrategy( pMotionUFO_myMotion );
    pObserver_myObserver->addChannel( pChannel_myChannel );
    pObserver_myObserver->addAttachment( pEnv_myEnv );
    pObserver_myObserver->setScene( pScene_myScene );

    pScene_myScene->addChild( pObject_myObject );





    pEnv_myEnv->addEnvFx( pEnvSun_myEnvSun );
    pEnv_myEnv->addEnvFx( pEnvMoon_myEnvMoon );
    pEnv_myEnv->addEnvFx( pEnvSkyDome_myEnvSkyDome );
    pEnv_myEnv->addEnvFx( pEnvCloudLayer2D_myEnvCloudLayer );
    pEnv_myEnv->addEnvFx( pEnvWind_myEnvWind );
    pEnv_myEnv->addEnvFx( pEnvStars_myEnvStars );









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

    // create my app instance
    vpApp *app = new vpApp;

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

