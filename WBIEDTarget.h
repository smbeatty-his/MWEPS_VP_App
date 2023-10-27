#ifndef WBIED_TARGET_MODULE_H
#define WBIED_TARGET_MODULE_H

#include <MarineTarget.h>


class WBIEDTarget : public MarineTarget
{
public:

	virtual ~WBIEDTarget(void);
	virtual int Configure(void);
	virtual void Update(const double dTime);
	virtual void PopulateTarget(const char* sTargetName);
	virtual void InstanceTarget(ITarget* pkTarget, const char* sInstanceName);
	virtual inline const char* GetClassname(void) const { return "WBIEDTarget"; }
	virtual inline void SetTargetedObject(vpObject* pkTargetedObject) { m_pkTargetedObject = pkTargetedObject; }
	
	void Detonate(void);
	void CheckProximityToTarget(void);

protected:

private:

	WBIEDTarget(void);

	vpObject* m_pkTargetedObject;
	bool m_bArmed;
	double m_dDetonationThreshold;
};

#endif