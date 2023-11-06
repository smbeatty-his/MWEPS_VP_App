#ifndef SCENARIO_PARSER_MODULE_H
#define SCENARIO_PARSER_MODULE_H

#include <DebugUtil.h>
#include <XMLParser.h>
#include <vuList.h>
#include <tinyxml2.h>

namespace tinyxml2 {
	class XMLNode;
}

class ITarget;
class MWEPSApp;

using namespace tinyxml2;

class ScenarioParser : public XMLParser
{
public:

	ScenarioParser(MWEPSApp* pkApp);
	virtual ~ScenarioParser();
	virtual void ParseFile(const char* sFilename);


private:
	
	void ParseTargetTypes(XMLNode* pkNode);
	void ParseEffectTypes(XMLNode* pkNode);
	void ParseSoundFiles(XMLNode* pkNode);
	void ParseTargetInstances(XMLNode* pkNode);
	void ParseSurfaceTypes(XMLNode* pkNode);
	void ParseTargetType(XMLNode* pkNode);
	void ParseEffectType(XMLNode* pkNode);
	void ParseSoundFile(XMLNode* pkNode);
	void ParseTargetInstance(XMLNode* pkNode);
	void ParseSurfaceType(XMLNode* pkNode);
	void ParseWayPointSets(XMLNode* pkNode);
	void ParseTargetWayPointSets(XMLNode* pkNode, ITarget* pkTarget);
	// SMB 06Nov2023 - Removed Crosshair from .xml file - could never get it working after updgrade to VP22
	//				   This functionality is now described in the.acf file
	//void ParseCrosshair(XMLNode* pkNode);
	void ParseSteeringBehaviors(XMLNode* pkNode, ITarget* pkTarget);
	void ParseEndTime(XMLNode* pkNode);
	void ParseMouseCursorEnabled(XMLNode* pkNode);
	void ParseOceanEnabled(XMLNode* pkNode);

	MWEPSApp* m_pkApp;
};

#endif