#ifndef HIT_REGION_MODULE_H
#define HIT_REGION_MODULE_H

#include <IHitRegion.h>
#include <Factory.h>

class HitRegion : public IHitRegion
{
public:

	HitRegion(void);
	virtual ~HitRegion(void);
	inline virtual const char* GetClassName(void) const { return "HitRegion"; } 

	ConcreteFactory(IHitRegion, HitRegion)

private:
	
};

typedef HitRegion::HitRegionFactory HitRegionFactory;

#endif
