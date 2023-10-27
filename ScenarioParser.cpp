#include <tinyxml2.h>
#include <ScenarioParser.h>
#include <TargetParser.h>
#include <vcConfigParser.h>
#include <vpFxParticleSystem.h>
#include <ParticleSystemManager.h>
#include <SoundManager.h>
#include <TargetManager.h>
#include <ISound.h>
#include <ITarget.h>
#include <Factory.h>
#include <FactoryManager.h>
#include <SurfaceType.h>
#include <XMLParser.h>
#include <vpPathWayPointSet.h>
#include <vpOverlay2DImage.h>
#include <AimManager.h>
#include <MWEPSApp.h>

using namespace tinyxml2;

ScenarioParser::ScenarioParser(MWEPSApp* pkApp) : m_pkApp(pkApp)
{
	
}

ScenarioParser::~ScenarioParser(void)
{

}

void ScenarioParser::ParseFile(const char* sFilename)
{

	// Was tinyxml --> TiXmlDocument kXMLDoc = XMLDocument(sFilename);
	XMLDocument kXMLDoc = XMLDocument();

	kXMLDoc.LoadFile(sFilename);

	// SMB 2 was: tinyxml2::XMLNode* pkNode = kXMLDoc.FirstChild()->FirstChild();
	auto* pkNode = kXMLDoc.FirstChild()->FirstChild();

	ASSERT(pkNode)
	ASSERT(!strcmp(pkNode->Value(), "Description"))

	pkNode = pkNode->NextSibling();

	ASSERT(pkNode)
	ASSERT(!strcmp(pkNode->Value(), "Environment"))	
	
	pkNode = pkNode->NextSibling();

	ASSERT(pkNode)
	ASSERT(! strcmp(pkNode->Value(), "EffectTypes"))	

	ParseEffectTypes(pkNode);

	pkNode = pkNode->NextSibling();
	ASSERT(pkNode)
	ASSERT(! strcmp(pkNode->Value(), "SoundFiles"))

	ParseSoundFiles(pkNode);

	pkNode = pkNode->NextSibling();
	ASSERT(pkNode)
	ASSERT(! strcmp(pkNode->Value(), "Crosshair"))

	ParseCrosshair(pkNode);

	pkNode = pkNode->NextSibling();
	ASSERT(pkNode)
	ASSERT(! strcmp(pkNode->Value(), "SurfaceTypes"))

	ParseSurfaceTypes(pkNode);

	pkNode = pkNode->NextSibling();
	ASSERT(pkNode)

	if(! strcmp(pkNode->Value(), "WayPointSets"))
	{
		ParseWayPointSets(pkNode);
		pkNode = pkNode->NextSibling();
	}
	
	ASSERT(pkNode)
	ASSERT(! strcmp(pkNode->Value(), "ScenarioEndTime"))

	ParseEndTime(pkNode);

	pkNode = pkNode->NextSibling();
	ASSERT(pkNode)
	ASSERT(! strcmp(pkNode->Value(), "MouseCursorEnabled"))

	ParseMouseCursorEnabled(pkNode);

	pkNode = pkNode->NextSibling();

	if (! strcmp(pkNode->Value(), "OceanEnabled"))
	{
		ParseOceanEnabled(pkNode);

		pkNode = pkNode->NextSibling();
	}

	ASSERT(pkNode)
	ASSERT(! strcmp(pkNode->Value(), "TargetTypes"))
	
	ParseTargetTypes(pkNode);

	pkNode = pkNode->NextSibling();
	ASSERT(pkNode)
	ASSERT(! strcmp(pkNode->Value(), "TargetInstances"))

	ParseTargetInstances(pkNode);
}

void ScenarioParser::ParseTargetTypes(XMLNode *pkNode)
{
	ASSERT(pkNode)
	
	XMLNode* pkTargetType = pkNode->FirstChild();

	while (pkTargetType)
	{
		ParseTargetType(pkTargetType);
		pkTargetType = pkTargetType->NextSibling();
	}
}

void ScenarioParser::ParseEffectTypes(XMLNode *pkNode)
{
	ASSERT(pkNode)

	XMLNode* pkEffectType = pkNode->FirstChild();

	while (pkEffectType)
	{
		ParseEffectType(pkEffectType);
		pkEffectType = pkEffectType->NextSibling();
	}
}

void ScenarioParser::ParseSoundFiles(XMLNode* pkNode)
{
	ASSERT(pkNode)

	XMLNode* pkSoundFile = pkNode->FirstChild();

	while (pkSoundFile)
	{
		ParseSoundFile(pkSoundFile);
		pkSoundFile = pkSoundFile->NextSibling();
	}
}

void ScenarioParser::ParseTargetInstances(XMLNode* pkNode)
{
	ASSERT(pkNode)

	XMLNode* pkTargetInstance = pkNode->FirstChild();

	while (pkTargetInstance)
	{
		ParseTargetInstance(pkTargetInstance);
		pkTargetInstance = pkTargetInstance->NextSibling();
	}
}

void ScenarioParser::ParseSurfaceTypes(XMLNode* pkNode)
{
	ASSERT(pkNode)

	XMLNode* pkSurfaceType = pkNode->FirstChild();

	while(pkSurfaceType)
	{
		ParseSurfaceType(pkSurfaceType);
		pkSurfaceType = pkSurfaceType->NextSibling();
	}
}

void ScenarioParser::ParseWayPointSets(XMLNode *pkNode)
{
	ASSERT(pkNode)

	const char* sFileName = pkNode->FirstChild()->FirstChild()->Value();

	vcConfigParser* pkParser = vcConfigParser::getTheConfigParser();
    pkParser->initialize();
    pkParser->setValidationScheme( vcConfigParser::NEVER_VALIDATE );
	pkParser->parse(sFileName);
    pkParser->finishParse();
}

void ScenarioParser::ParseCrosshair(XMLNode* pkNode)
{
	XMLNode* pkChild = pkNode->FirstChild();

	const char* sFilename = pkChild->FirstChild()->Value();	
	pkChild = pkChild->NextSibling();

	const char* sScale = pkChild->FirstChild()->Value();
	vuVec2<float> vfScale;

	XMLParser::ParseVec2(&vfScale, sScale);

	vpOverlay2DImage* pkCrosshair = new vpOverlay2DImage();  //SMB check

	ASSERT(pkCrosshair)

	int iImageLoad = pkCrosshair->addImageFile(sFilename); //SMB check

	ASSERT(iImageLoad == vsgu::SUCCESS)

	pkCrosshair->setScale(vfScale[0], vfScale[1]); //SMB check 0.03 and 0.05

//	pkCrosshair->configure(); // Goes to VpOverlay configure - no source for this. No longer called? Removing didn't change behavior

	pkCrosshair->setEnable(true); //SMB check

	AimManager::GetInstance()->SetCrosshair(pkCrosshair); // Points m_pkCrosshair to this object, sets Scale Adjustment
	pkCrosshair->setName("myMissingCrosshair"); //SMB check
	pkCrosshair->setDisplayTime(5000); //SMB check
	pkCrosshair->setOrigin(0.75000f, 0.75000f);  //SMB check
	//pkCrosshair->setScale(0.260000f, 0.240000f); //SMB check
	pkCrosshair->setFadeInDuration(0); //SMB check
	pkCrosshair->setFadeOutDuration(0); //SMB check
	pkCrosshair->setBlinkingEnable(false); //SMB check
	pkCrosshair->setRenderingPriority(100); //SMB check

	//AimManager::GetInstance()->SetCrosshair(pkCrosshair); // Points m_pkCrosshair to this object, sets Scale Adjustment

	// This code copied directly from Presagis example RedAim_overlay.cpp - doesn't display the .png file
/*
	vpOverlay2DImage* pOverlay2DImage_myOverlay2DImage = new vpOverlay2DImage(); //SMB check
	pOverlay2DImage_myOverlay2DImage->setName("myOverlay2DImage"); //SMB check
	pOverlay2DImage_myOverlay2DImage->setEnable(true); //SMB check
	pOverlay2DImage_myOverlay2DImage->addImageFile("RedBlueAim.png"); //SMB check
	pOverlay2DImage_myOverlay2DImage->setDisplayTime(5000); //SMB check
	pOverlay2DImage_myOverlay2DImage->setOrigin(0.185000f, 0.155000f);  //SMB check
	pOverlay2DImage_myOverlay2DImage->setScale(0.460000f, 0.440000f); //SMB check
	pOverlay2DImage_myOverlay2DImage->setFadeInDuration(0); //SMB check
	pOverlay2DImage_myOverlay2DImage->setFadeOutDuration(0); //SMB check
	pOverlay2DImage_myOverlay2DImage->setBlinkingEnable(false); //SMB check
	pOverlay2DImage_myOverlay2DImage->setRenderingPriority(100); //SMB check
*/
	//AimManager::GetInstance()->SetCrosshair(pOverlay2DImage_myOverlay2DImage); // Points m_pkCrosshair to this object, sets Scale Adjustment

}

void ScenarioParser::ParseTargetType(XMLNode* pkNode)
{
	ASSERT(pkNode)

	const char* const  pkFileName = pkNode->FirstChild()->FirstChild()->Value();

	TargetParser kTarget;
	kTarget.ParseFile(pkFileName);
}

void ScenarioParser::ParseEffectType(XMLNode *pkNode)
{
	ASSERT(pkNode)

	const char* const  sFileName = pkNode->FirstChild()->FirstChild()->Value();
	XMLElement* pkElement = (XMLElement*) pkNode;
	ASSERT(pkElement)

	vcConfigParser* pkParser = vcConfigParser::getTheConfigParser();
    pkParser->initialize();
    pkParser->setValidationScheme( vcConfigParser::NEVER_VALIDATE );
	pkParser->parse(sFileName);
    pkParser->finishParse();

	const char* sParticleName = pkElement->FirstAttribute()->Value();

	ASSERT(sParticleName)
	
	vpFxParticleSystem* pkSystem = vpFxParticleSystem::find(sParticleName);

	ASSERT(pkSystem)

	ParticleSystemManager::GetInstance()->RegisterParticleSystem(sParticleName, pkSystem);
}

void ScenarioParser::ParseSoundFile(XMLNode* pkNode)
{
	ASSERT(pkNode)
	
	XMLNode* pkChild = pkNode->FirstChild();

	const char* sFileName =  pkChild->FirstChild()->Value();

	const char* sSoundName = ((XMLElement*)pkNode)->FirstAttribute()->Value();

	ISound* pkSound = FactoryManager::GetInstance()->CreateSound(pkNode->Value());

	pkSound->ParseData(pkChild->NextSibling());

	pkSound->LoadSound(sFileName);

	SoundManager::GetInstance()->AddSound(pkSound, sSoundName);
}

void ScenarioParser::ParseTargetInstance(XMLNode *pkNode)
{
	ASSERT(pkNode)

	XMLNode* pkChild = pkNode->FirstChild();

	const char* sTargetName =  pkChild->FirstChild()->Value();

	const char* sInstanceName = ((XMLElement*)pkNode)->FirstAttribute()->Value();

	ITarget* pkMasterTarget = TargetManager::GetInstance()->GetTargetType(sTargetName);

	ITarget* pkTarget = FactoryManager::GetInstance()->CreateTarget(pkMasterTarget->GetClassname());

	pkTarget->InstanceTarget(pkMasterTarget, sInstanceName);

	vuMap<CharPointer, const char*> msTagMap;

	pkChild = pkChild->NextSibling();

	while (pkChild)
	{
		ASSERT(pkChild->FirstChild())
		
		if (! strcmp(pkChild->Value(), "WayPointSets"))
		{
			ParseTargetWayPointSets(pkChild, pkTarget);
		}

		else if (! strcmp(pkChild->Value(), "SteeringBehaviors"))
		{
			ParseSteeringBehaviors(pkChild, pkTarget);
		}

		else
		{
			msTagMap.insert(std::pair<CharPointer, const char*>(pkChild->Value(), pkChild->FirstChild()->Value()));
		}
		
		pkChild = pkChild->NextSibling();
	}

	if (msTagMap.count("Position"))
	{
		vuVec3<double> vdPos;
		ParseVec3(&vdPos, msTagMap.find("Position")->second);
		pkTarget->GetTargetObject()->setTranslate(vdPos[0], vdPos[1], vdPos[2]);
		pkTarget->SetStartPosition(vdPos);
	}

	if (msTagMap.count("Rotation"))
	{
		vuVec3<double> vdRotation;
		ParseVec3(&vdRotation, msTagMap.find("Rotation")->second);
		pkTarget->GetTargetObject()->setRotate(vdRotation[0], vdRotation[1], vdRotation[2]);
		pkTarget->SetStartRotation(vdRotation);
	}

	if (msTagMap.count("Scale"))
	{
		vuVec3<double> vdScale;
		ParseVec3(&vdScale, msTagMap.find("Scale")->second);
		pkTarget->GetTargetObject()->setScale(vdScale[0], vdScale[1], vdScale[2]);
	}

	if (msTagMap.count("StartTime"))
	{
		pkTarget->SetStartTime(atof(msTagMap.find("StartTime")->second));
	}

	if (msTagMap.count("StartPathIndex"))
	{
		ASSERT(msTagMap.count("StartWayPointIndex"))
		int iIndex = atoi(msTagMap.find("StartPathIndex")->second);
		pkTarget->SetStartingWayPointSet(iIndex);
		pkTarget->SetActiveWayPointSet(iIndex);
	}

	if (msTagMap.count("StartWayPointIndex"))
	{
		ASSERT(msTagMap.count("StartPathIndex"))
		pkTarget->SetWayPointIndex(atoi(msTagMap.find("StartWayPointIndex")->second));
		pkTarget->SetStartingWayPointIndex(pkTarget->GetWayPointIndex());
		
	}
	
	TargetManager::GetInstance()->AddInstance(pkTarget);
}

void ScenarioParser::ParseSurfaceType(XMLNode* pkNode)
{
	ASSERT(pkNode)

	const char* sName = ((XMLElement*)pkNode)->FirstAttribute()->Value();

	XMLNode* pkChild = pkNode->FirstChild();

	vuMap<CharPointer, const char*> msTagMap;

	while (pkChild)
	{
		msTagMap.insert(std::pair<CharPointer, const char*>(pkChild->Value(), pkChild->FirstChild()->Value()));
		pkChild = pkChild->NextSibling();
	}

	SurfaceType* pkType = new SurfaceType();

	if (msTagMap.count("HitSound"))
	{
		pkType->SetSoundName(msTagMap.find("HitSound")->second);
	}

	if (msTagMap.count("HitEffect"))
	{
		pkType->SetEffectName(msTagMap.find("HitEffect")->second);
	}

	if (msTagMap.count("HitEffectScale"))
	{
		vuVec3<double> vdScale;
		XMLParser::ParseVec3(&vdScale, msTagMap.find("HitEffectScale")->second);
		pkType->SetEffectScale(vdScale);
	}

	TargetManager::GetInstance()->AddSurfaceType(sName, pkType);
}

void ScenarioParser::ParseTargetWayPointSets(XMLNode *pkNode, ITarget* pkTarget)
{
	ASSERT(pkNode)
	ASSERT(pkTarget)

	XMLNode* pkChild = pkNode->FirstChild();

	ASSERT(pkChild)

	while (pkChild)
	{
		const char* sName = pkChild->FirstChild()->FirstChild()->Value();

		vpPathWayPointSet* pkWayPointSet = NULL;
		
		pkWayPointSet = vpPathWayPointSet::find(sName);

		pkTarget->AttachWayPointSet(pkWayPointSet);
		pkChild = pkChild->NextSibling();
	}
}

void ScenarioParser::ParseSteeringBehaviors(XMLNode* pkNode, ITarget* pkTarget)
{
	ASSERT(pkNode)
	ASSERT(pkTarget)

	XMLNode* pkChild = pkNode->FirstChild();

	ASSERT(pkChild)

	while (pkChild)
	{
		XMLNode* pkBehaviorNode = pkChild->FirstChild();
		
		const char* sClassname = pkBehaviorNode->FirstChild()->Value();

		ISteeringBehavior* pkBehavior = FactoryManager::GetInstance()->CreateSteeringBehavior(sClassname);

		pkBehaviorNode = pkBehaviorNode->NextSibling();

		const double dWeight = atof(pkBehaviorNode->FirstChild()->Value());

		pkBehavior->SetWeight(dWeight);

		pkTarget->AddSteeringBehavior(pkBehavior);

		pkChild = pkChild->NextSibling();
	}
}

void ScenarioParser::ParseEndTime(XMLNode *pkNode)
{
	ASSERT(pkNode)

	m_pkApp->SetEndTime(atof(pkNode->FirstChild()->FirstChild()->Value()));
}

void ScenarioParser::ParseMouseCursorEnabled(XMLNode* pkNode)
{
	ASSERT(pkNode)

	int iVal = atoi(pkNode->FirstChild()->Value());
	(*vpWindow::begin())->setCursorEnable(iVal != 0);
}

void ScenarioParser::ParseOceanEnabled(XMLNode *pkNode)
{
	ASSERT(pkNode)

	int iVal = atoi(pkNode->FirstChild()->Value());
	m_pkApp->SetEnableOcean(iVal != 0);
}