#include <WBIEDTarget.h>

WBIEDTarget::WBIEDTarget(void) : m_bArmed(true), m_pkTargetedObject(NULL), m_dDetonationThreshold(50.0)
{

}

WBIEDTarget::~WBIEDTarget(void)
{

}

int WBIEDTarget::Configure(void)
{
	return 0;
}

void WBIEDTarget::Update(const double dTime)
{
	if (m_bArmed)
	{
		CheckProximityToTarget();
		MarineTarget::Update(dTime);
	}
}

void WBIEDTarget::PopulateTarget(const char* sTargetName)
{
	ASSERT(sTargetName);

	MarineTarget::PopulateTarget(sTargetName);
}

void WBIEDTarget::InstanceTarget(ITarget* pkTarget, const char* sInstanceName)
{
	ASSERT(pkTarget)
	ASSERT(dynamic_cast<WBIEDTarget*>(pkTarget) != NULL)

	MarineTarget::InstanceTarget(pkTarget, sInstanceName);
}

void WBIEDTarget::CheckProximityToTarget(void)
{
	vuVec3<double> vdWBIEDPos;
	GetTargetObject()->getTranslate(&(vdWBIEDPos[0]), &(vdWBIEDPos[1]), &(vdWBIEDPos[2]));

	vuVec3<double> vdTargetedPos;
	m_pkTargetedObject->getTranslate(&(vdTargetedPos[0]), &(vdTargetedPos[1]), &(vdTargetedPos[2]));

	vdWBIEDPos += vdTargetedPos * -1;

	if (vdWBIEDPos.length())
	{
		Detonate();
	}
}

void WBIEDTarget::Detonate(void)
{
	m_bArmed = false;
	SetState(DETONATED);
	ProcessStateChange();
}