#include <TargetParser.h>
#include <TinyXml2.h>
#include <vcConfigParser.h>
#include <TargetManager.h>
#include <ParticleSystemManager.h>
#include <ITarget.h>
#include <IHitRegion.h>
#include <Factory.h>
#include <HitRegionParser.h>
#include <vuVector.h>
#include <vpFxParticleSystem.h>
#include <FactoryManager.h>
#include <AttachedParticleSystem.h>
#include <SoundManager.h>
#include <SoundAttachedNode.h>

TargetParser::TargetParser(void)
{

}

TargetParser::~TargetParser(void)
{

}

void TargetParser::ParseFile(const char* sFilename)
{
	ASSERT(sFilename)

	XMLDocument kXMLDoc = XMLDocument();

	kXMLDoc.LoadFile(sFilename);

	XMLNode* pkNode = kXMLDoc.FirstChild();

	const char* sTargetName = ((XMLElement*)pkNode)->FirstAttribute()->Value();

	XMLNode* pkChild = pkNode->FirstChild();

	vuMap<CharPointer, const char*> mpkTagMap;
	vuMap<ITarget::TargetState, vuVector<AttachedParticleSystem*>*> mpkEffectMap; 

	ASSERT(! strcmp(pkChild->Value(), "ClassType"))

	m_pkTarget = FactoryManager::GetInstance()->CreateTarget(pkChild->FirstChild()->Value());

	pkChild = pkChild->NextSibling();

	ASSERT(!strcmp(pkChild->Value(), "Filename"))

	//const char* sFileName = pkChild->FirstChild()->Value();

	//vcConfigParser* pkParser = vcConfigParser::getTheConfigParser();
	//pkParser->initialize();
	//pkParser->setValidationScheme( vcConfigParser::NEVER_VALIDATE );
	//pkParser->parse(sFileName);
	//pkParser->finishParse();

	m_pkTarget->PopulateTarget(sTargetName);

	pkChild = pkChild->NextSibling();

	while (pkChild)
	{
		if (! strcmp(pkChild->Value(), "Effect"))
		{
			XMLNode* pkEffectNode = pkChild->FirstChild();

			ITarget::TargetState kState = (ITarget::TargetState) atoi(pkEffectNode->FirstChild()->Value());
			
			if (! mpkEffectMap.count(kState))
			{
				vuVector<AttachedParticleSystem*>* pkVector = new vuVector<AttachedParticleSystem*>();
				mpkEffectMap.insert(std::pair<ITarget::TargetState, vuVector<AttachedParticleSystem*>*>
													(kState, pkVector));
			}

			vuVector<AttachedParticleSystem*>* pkVector = mpkEffectMap.find(kState)->second;

			AttachedParticleSystem* pkSystem = new AttachedParticleSystem();
			pkSystem->SetParticleSystem(ParticleSystemManager::GetInstance()->SpawnParticleSystem
												(((XMLElement*)pkChild)->FirstAttribute()->Value()));

			pkEffectNode = pkEffectNode->NextSibling();

			vuMap<CharPointer, const char*> msMap;

			while (pkEffectNode)
			{
				msMap.insert(std::pair<CharPointer, const char*>
									(pkEffectNode->Value(), pkEffectNode->FirstChild()->Value()));
				pkEffectNode = pkEffectNode->NextSibling();
			}

			if (msMap.count("Scale"))
			{
				vuVec3<double> vdScale;
				XMLParser::ParseVec3(&vdScale, msMap.find("Scale")->second);
				pkSystem->GetParticleSystem()->setScale(vdScale[0], vdScale[1], vdScale[2]);
			}

			if (msMap.count("Offset"))
			{
				vuVec3<double> vdOffset;
				XMLParser::ParseVec3(&vdOffset, msMap.find("Offset")->second);
				pkSystem->SetOffset(vdOffset);
			}

			if (msMap.count("EndTargetState"))
			{
				pkSystem->SetTargetEndState(atoi(msMap.find("EndTargetState")->second));
			}

			pkVector->push_back(pkSystem);
			
		}

		if (! strcmp(pkChild->Value(), "Sounds"))
		{
			ParseSounds(pkChild);
		}
		
		if (! strcmp(pkChild->Value(), "HitRegions"))
		{
			ParseHitRegions(pkChild);
		}

		if (! strcmp(pkChild->Value(), "CenterOfMassOffset"))
		{
			vuVec3<double> vdCenterOfMassOffset;
			XMLParser::ParseVec3(&vdCenterOfMassOffset, pkChild->FirstChild()->Value());
			m_pkTarget->SetCenterOfMassOffset(vdCenterOfMassOffset);
		}

		else
		{
			mpkTagMap.insert(std::pair<CharPointer, const char*>(pkChild->Value(), pkChild->FirstChild()->Value()));
		}

		pkChild = pkChild->NextSibling();
	}
	
	ProcessMap(mpkTagMap);
	
	ASSERT(m_pkTarget)

	m_pkTarget->SetEffectMap(mpkEffectMap);
	TargetManager::GetInstance()->AddTarget(sTargetName, m_pkTarget);

	(*vpScene::begin())->addChild(m_pkTarget->GetTargetObject());
// SMB 21 Aug 2023: commented out removeChild so that Target shows up immediately - did not work
	(*vpScene::begin())->removeChild(m_pkTarget->GetTargetObject());
}

void TargetParser::ProcessMap(const vuMap<CharPointer, const char*>& msTagMap)
{
	if (msTagMap.count("HitPoints"))
	{
		m_pkTarget->SetHitPoints(atoi(msTagMap.find("HitPoints")->second));
		m_pkTarget->SetStartingHitPoints(m_pkTarget->GetHitPoints());
	}

	if (msTagMap.count("MaxSpeed"))
	{
		m_pkTarget->SetMaxSpeed(atof(msTagMap.find("MaxSpeed")->second));
	}

	if (msTagMap.count("StartTime"))
	{
		m_pkTarget->SetStartTime(atof(msTagMap.find("StartTime")->second));
	}

	if (msTagMap.count("HitPointThresholds"))
	{
		char sValString[256];

		strcpy(sValString, msTagMap.find("HitPointThresholds")->second);

		char* sToken = strtok(sValString, ",");
		int iIndex = 0;

		while (sToken != NULL)
		{
			int iHPs = atof(sToken);
			m_pkTarget->SetHitPointThreshold(iHPs, iIndex);
			sToken = strtok(NULL, ",");
			++iIndex;
		}

		ASSERT(iIndex == 4)
	}

	if (msTagMap.count("MaxForce"))
	{
		m_pkTarget->SetMaxForce(atof(msTagMap.find("MaxForce")->second));
	}

	if (msTagMap.count("DecelerationRate"))
	{
		m_pkTarget->SetDecelerationRate(atof(msTagMap.find("DecelerationRate")->second));
	}

}

void TargetParser::ParseHitRegions(XMLNode* pkNode)
{
	XMLNode* pkChild = pkNode->FirstChild();

	while (pkChild)
	{
		const char* sName = ((XMLElement*)pkChild)->FirstAttribute()->Value();

		HitRegionParser kParser;

		IHitRegion* pkRegion = kParser.Parse(pkChild);

		m_pkTarget->AddHitRegion(sName, pkRegion);

		pkChild = pkChild->NextSibling();
	}
}

void TargetParser::ParseSounds(XMLNode* pkNode)
{
	XMLNode* pkChild = pkNode->FirstChild();

	ASSERT(pkChild)
	ASSERT(m_pkTarget)

	vuMap<ITarget::TargetState, vuVector<SoundAttachedNode*>*> mpkStateSounds;

	while (pkChild)
	{
		const char* sName = ((XMLElement*)pkChild)->FirstAttribute()->Value();

		XMLNode* pkValue = pkChild->FirstChild();

		vuMap<CharPointer, const char*> mpkTagMap;

		while (pkValue)
		{
			mpkTagMap.insert(std::pair<CharPointer, const char*>(pkValue->Value(), pkValue->FirstChild()->Value()));
			pkValue = pkValue->NextSibling();
		}

		SoundAttachedNode* pkAttachedNode;

		if (! mpkTagMap.count("ClassType"))
		{
			pkAttachedNode = SoundManager::GetInstance()->SpawnAttachedSound(sName, "SoundAttachedNode");
		}

		else
		{
			const char* sClassType = mpkTagMap.find("ClassType")->second;

			pkAttachedNode = SoundManager::GetInstance()->SpawnAttachedSound(sName, sClassType);
		}

		ASSERT(mpkTagMap.count("StartState"))
		ASSERT(mpkTagMap.count("EndState"))

		pkAttachedNode->ProcessData(mpkTagMap);

		ITarget::TargetState kStartState = (ITarget::TargetState) pkAttachedNode->GetStartState();

		if (! mpkStateSounds.count(kStartState))
		{
			vuVector<SoundAttachedNode*>* pkVector = new vuVector<SoundAttachedNode*>();

			mpkStateSounds.insert(std::pair<ITarget::TargetState, vuVector<SoundAttachedNode*>*>
																		(kStartState, pkVector));
		}

		vuVector<SoundAttachedNode*>* pkVector = mpkStateSounds.find(kStartState)->second;

		pkVector->push_back(pkAttachedNode);

		m_pkTarget->GetTargetObject()->addChild(pkAttachedNode);

		pkChild = pkChild->NextSibling();
	}

	m_pkTarget->SetSoundMap(mpkStateSounds);
}