#ifndef HIT_REGION_PARSER_MODULE_H
#define HIT_REGION_PARSER_MODULE_H

#include <DebugUtil.h>
#include <vuMap.h>
#include <CharPointer.h>
#include <vuVector.h>
#include <IHitRegion.h>
#include <tinyxml2.h>

namespace tinyxml2 {
	class XMLNode;
}
class vpFxParticleSystem;
class AttachedParticleSystem;

class HitRegionParser

{

public:

	HitRegionParser(void);
	~HitRegionParser(void);
	IHitRegion* Parse(tinyxml2::XMLNode* pkNode);
	void ParseEffect(vuMap<IHitRegion::RegionState, vuVector<AttachedParticleSystem*>*>& mpkEffectsMap, tinyxml2::XMLNode* pkNode);
	void ProcessMap(vuMap<CharPointer, const char*>& msTagMap);

private:

	IHitRegion* m_pkRegion;
};

#endif