#include <HitRegionParser.h>
#include <IHitRegion.h>
#include <vuMap.h>
#include <CharPointer.h>
#include <tinyxml2.h>
#include <ParticleSystemManager.h>
#include <XMLParser.h>
#include <vpFxParticleSystem.h>
#include <FactoryManager.h>
#include <AttachedParticleSystem.h>

HitRegionParser::HitRegionParser(void)
{

}

HitRegionParser::~HitRegionParser(void)
{

}

IHitRegion* HitRegionParser::Parse(tinyxml2::XMLNode* pkNode)
{
	vuMap<CharPointer, const char*> msTagMap;
	vuMap<IHitRegion::RegionState, vuVector<AttachedParticleSystem*>*> mpkEffectsMap;

	//SMB 2 was: tinyxml2::XMLNode* pkChild = pkNode->FirstChild();
	auto* pkChild = pkNode->FirstChild();
	m_pkRegion = NULL;

	while (pkChild)
	{
		if (! strcmp(pkChild->Value(), "Effect"))
		{
			ParseEffect(mpkEffectsMap, pkChild);
		}

		else if (! strcmp(pkChild->Value(), "ClassType"))
		{
			m_pkRegion = FactoryManager::GetInstance()->CreateHitRegion(pkChild->FirstChild()->Value());

			ASSERT(m_pkRegion)
		}

		else
		{
			msTagMap.insert(std::pair<CharPointer, const char*>(pkChild->Value(), pkChild->FirstChild()->Value()));
		}

		pkChild = pkChild->NextSibling();
	}

	ASSERT(m_pkRegion)

	m_pkRegion->SetEffectMap(mpkEffectsMap);

	ProcessMap(msTagMap);
		
	return m_pkRegion;
}

void HitRegionParser::ProcessMap(vuMap<CharPointer,const char *>& msTagMap)
{
	if (msTagMap.count("HitPoints"))
	{
		m_pkRegion->SetHitPoints(atoi(msTagMap.find("HitPoints")->second));
		m_pkRegion->SetStartingHitPoints(m_pkRegion->GetHitPoints());
	}

	if (msTagMap.count("AreaHitPointValue"))
	{
		m_pkRegion->SetAreaHitPointValue(atoi(msTagMap.find("AreaHitPointValue")->second));
	}

	if (msTagMap.count("SurfaceType"))
	{
		m_pkRegion->SetSurfaceType(msTagMap.find("SurfaceType")->second);
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
			m_pkRegion->SetHitPointThreshold(iHPs, iIndex);
			sToken = strtok(NULL, ",");
			++iIndex;
		}

		ASSERT(iIndex == 4)
	}
}

void HitRegionParser::ParseEffect(vuMap<IHitRegion::RegionState,vuVector<AttachedParticleSystem*>*>& mpkEffectsMap,
	tinyxml2::XMLNode* pkNode)
{
	tinyxml2::XMLNode* pkChild = pkNode->FirstChild();

	IHitRegion::RegionState kState = (IHitRegion::RegionState) atoi(pkChild->FirstChild()->Value());
			
	if (! mpkEffectsMap.count(kState))
	{
		mpkEffectsMap.insert(std::pair<IHitRegion::RegionState, vuVector<AttachedParticleSystem*>*>
													(kState, new vuVector<AttachedParticleSystem*>()));
	}

	vuVector<AttachedParticleSystem*>* pkVector = mpkEffectsMap.find(kState)->second;

	AttachedParticleSystem* pkSystem = new AttachedParticleSystem();
	pkSystem->SetParticleSystem(ParticleSystemManager::GetInstance()->SpawnParticleSystem
									(((tinyxml2::XMLElement*)pkNode)->FirstAttribute()->Value()));
	
	vuMap<CharPointer, const char*> msTagMap;

	pkChild = pkChild->NextSibling();

	while (pkChild)
	{
		msTagMap.insert(std::pair<CharPointer, const char*>(pkChild->Value(), pkChild->FirstChild()->Value()));
		pkChild = pkChild->NextSibling();
	}

	if (msTagMap.count("Scale"))
	{
		vuVec3<double> vdScale;
		XMLParser::ParseVec3(&vdScale, msTagMap.find("Scale")->second);
		pkSystem->GetParticleSystem()->setScale(vdScale[0], vdScale[1], vdScale[2]);
	}

	if (msTagMap.count("Offset"))
	{
		vuVec3<double> vdOffset;
		XMLParser::ParseVec3(&vdOffset, msTagMap.find("Offset")->second);
		pkSystem->SetOffset(vdOffset);
	}

	if (msTagMap.count("EndTargetState"))
	{
		pkSystem->SetTargetEndState(atoi(msTagMap.find("EndTargetState")->second));
	}

	if (msTagMap.count("EndRegionState"))
	{
		pkSystem->SetTargetEndState(atoi(msTagMap.find("EndRegionState")->second));
	}

	pkVector->push_back(pkSystem);
}