#include <SteeringTarget.h>
#include <SteeringController.h>
#include <DefaultBehaviorState.h>

SteeringTarget::SteeringTarget(void) : ITarget()
{
	m_pkSteeringController = new SteeringController();
	m_pkBehaviorState = DefaultBehaviorState::GetInstance();
}

void SteeringTarget::Update(const double dTime)
{
	vuVec3<double> vdPrevPos;
	GetTargetObject()->getTranslate(&(vdPrevPos[0]), &(vdPrevPos[1]), &(vdPrevPos[2]));
	
	vuVec3<double> vdPrevOrient;
	GetTargetObject()->getOrientation(&(vdPrevOrient[0]), &(vdPrevOrient[1]), &(vdPrevOrient[2]));

	m_pkBehaviorState->Update(dTime, this);
	
	vuVec3<double> vdCurrPos;
	GetTargetObject()->getTranslate(&(vdCurrPos[0]), &(vdCurrPos[1]), &(vdCurrPos[2]));
	
	vuVec3<double> vdCurrOrient;
	GetTargetObject()->getOrientation(&(vdCurrOrient[0]), &(vdCurrOrient[1]), &(vdCurrOrient[2]));

	if (m_bLogStateChange || vdPrevPos != vdCurrPos || vdPrevOrient != vdCurrOrient)
	{
		UpdateTargetRecord();
	}

	m_bLogStateChange = false;
}

int SteeringTarget::Configure(void)
{
	return vsgu::SUCCESS;
}