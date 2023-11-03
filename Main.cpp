#include <Picker.h>
#include <MWEPSApp.h>
#include <ParticleSystemManager.h>
#include <BulletManager.h>
#include <AimManager.h>
#include <SoundManager.h>
#include <TargetManager.h>
#include <AARManager.h>
#include <GunManager.h>
#include <ALController.h>
#include <ITarget.h>
#include <MarineTarget.h>
#include <FactoryManager.h>
#include <TPManager.h>
#include <OceanManager.h>
#include <ViewManager.h>
#include <vpMarineGlobals.h>
#include <DefaultBehaviorState.h>
#include <PerformanceLogger.h>
//#include <vpOverlay2DImage.h>


void InitializeBehaviorStates(void);

int main(int argc, char *argv[])
{
	int i;
	printf("argc = %d\n", argc);
	for (i = 0; i < argc; i++)
	{
		printf("argv %d: %s\n", i, argv[i]);
	}

//	Sleep(13000); // SMB: wait 13 seconds to attach debugger

    // initialize vega prime
    vp::initialize(argc, argv);

    // create my app instance
    MWEPSApp* pkApp = new MWEPSApp();

	FactoryManager::Initialize();
	TPManager::Initialize("dsLane0");

	//Initialize OpenAL
	ALController::Initialize(&argc, argv);


	while (! TPManager::GetInstance()->ProcessInitialization(pkApp)) {  }
	printf("Main: ACF Filename: %s     Scenario Filename: %s \r\n", 
			pkApp->GetACFName(), pkApp->GetScenarioName());
	// Show the current working directory
//	TCHAR pwd[MAX_PATH];
//	GetCurrentDirectory(MAX_PATH, pwd);
//	MessageBox(NULL, pwd, pwd, 0);

    // load the acf file
    if (argc <= 1)
	{
		pkApp->define(pkApp->GetACFName());
	}
    else 
	{
		pkApp->define(argv[1]);
	}

	//Initialize Managers
	
	ParticleSystemManager::Initialize();
	BulletManager::Initialize();
	AimManager::Initialize();
	SoundManager::Initialize();
	TargetManager::Initialize();
	AARManager::Initialize();
	GunManager::Initialize();
	OceanManager::Initialize();
	ViewManager::Initialize();
	PerformanceLogger::Initialize();

	InitializeBehaviorStates();

	// configure my app
    pkApp->configure();

    // execute the main runtime loop
    pkApp->run();

    // delete my app instance
    pkApp->unref();

    // shutdown vega prime
    vp::shutdown();

    return 0;

}

void InitializeBehaviorStates(void)
{
	DefaultBehaviorState::Initialize();
}