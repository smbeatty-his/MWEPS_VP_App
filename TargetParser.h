#ifndef TARGET_PARSER_MODULE_H
#define TARGET_PARSER_MODULE_H

#include <DebugUtil.h>
#include <XMLParser.h>
#include <vuMap.h>
#include <vuVector.h>
#include <tinyxml2.h>

namespace tinyxml2 {
	class XMLNode;
}
class IHitRegion;
class ITarget;

using namespace tinyxml2;

class TargetParser : public XMLParser
{
public:

	TargetParser(void);
	virtual ~TargetParser(void);
	virtual void ParseFile(const char* sFilename);
	void ParseHitRegions(XMLNode* pkNode);
	void ParseSounds(XMLNode* pkNode);
	void ProcessMap(const vuMap<CharPointer, const char*>& pmTagMap);

private:

	ITarget* m_pkTarget;
	vuMap<CharPointer, IHitRegion*> m_mpkRegionMap;
};

#endif