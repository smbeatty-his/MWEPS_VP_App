#ifndef STATIONARY_TARGET_MODULE_H
#define STATIONARY_TARGET_MODULE_H

#include <ITarget.h>
#include <Factory.h>

class StationaryTarget : public ITarget
{
public:

	virtual ~StationaryTarget(void) { }
	virtual int Configure() { return 1; }
	virtual void Update(const double dTime) { } 
	virtual void PopulateTarget(const char* sTargetName) { }
	virtual void InstanceTarget(ITarget* pkTarget, const char* sInstanceName) { }
	virtual inline const char* GetClassname(void) const { return "StationaryTarget"; }
	virtual void ProcessHit(vsNode* pkNode) { }
	ConcreteFactory(ITarget, StationaryTarget)

private:
	
	StationaryTarget(void) { }
	float m_fExposureTime;
};

typedef StationaryTarget::StationaryTargetFactory StationaryTargetFactory;

#endif