#ifndef STEERING_TARGET_MODULE_H
#define STEERING_TARGET_MODULE_H

#include <DebugUtil.h>
#include <ITarget.h>

class SteeringTarget : public ITarget
{

public:
	virtual ~SteeringTarget(void) { }
	virtual int Configure();
	virtual void Update(const double dTime);
	virtual void PopulateTarget(const char* sTargetName) { };
	virtual void Reset(void) { ITarget::Reset(); }

	virtual void InstanceTarget(ITarget* pkTarget, const char* sInstanceName) 
								{ ITarget::InstanceTarget(pkTarget, sInstanceName); }

	virtual void ProcessHit(const char* sRegionName, const vuVec3<double>& vdHitPos)
								{ ITarget::ProcessHit(sRegionName, vdHitPos); }
	virtual inline const char* GetClassname(void) const { return "SteeringTarget"; }

	ConcreteFactory(ITarget, SteeringTarget)

protected:
	SteeringTarget(void);

private:

};

typedef SteeringTarget::SteeringTargetFactory SteeringTargetFactory;

#endif