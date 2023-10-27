#include <TargetManager.h>
#include <ITarget.h>
#include <MarineTarget.h>
#include <vpKernel.h>
#include <SurfaceType.h>
#include <vuList.h>
#include <vpMarineShip.h>
#include <vpOverlay2DImage.h>


TargetManager* TargetManager::s_pkInstance = NULL;

TargetManager::TargetManager(int iPulseRate) : m_iTargetPulseRate(iPulseRate)
{
	m_dTargetPulseDelay = 1.0 / iPulseRate;
	m_dTargetDelayedTime = 0.0;
}

TargetManager::~TargetManager(void)
{
	vuMap<CharPointer, ITarget*>::iterator kIter = m_mpkTargets.begin();

	while (kIter != m_mpkTargets.end())
	{
		delete kIter->second;
		++kIter;
	}

	vuList<ITarget*>::iterator kTargetIter = m_lpkTargetInstances.begin();

	while (kTargetIter != m_lpkTargetInstances.end())
	{
		ITarget* pkTarget = *kTargetIter;
		++kTargetIter;
		delete pkTarget;
	}

	vuMap<CharPointer, SurfaceType*>::iterator kSurfaceIter = m_mpkSurfaceTypes.begin();

	while (kSurfaceIter != m_mpkSurfaceTypes.end())
	{
		delete kSurfaceIter->second;
		++kSurfaceIter;
	}
}

void TargetManager::Update(double dSimTime, double dDeltaTime)
{

	vuList<ITarget*>::iterator kInactiveIter = m_lpkInactiveTargets.begin();
	
	while(kInactiveIter != m_lpkInactiveTargets.end())
	{
		ITarget* pkTarget = *kInactiveIter;

		if (pkTarget->GetStartTime() <= dSimTime)
		{
			pkTarget->SetState(ITarget::UNDAMAGED);
			(*vpScene::begin())->addChild(pkTarget->GetTargetObject());
			m_mpkActiveTargets.insert(std::pair<unsigned int, ITarget*>
								((unsigned int)pkTarget->GetTargetObject(), pkTarget));
			pkTarget->GetTargetObject()->setRenderMask(0xFFFFFFFF);

			kInactiveIter = m_lpkInactiveTargets.erase(kInactiveIter);
		}

		else
		{
			++kInactiveIter;
		}
	}

	vuMap<unsigned int, ITarget*>::iterator kActiveIter = m_mpkActiveTargets.begin();

	for (kActiveIter; kActiveIter != m_mpkActiveTargets.end(); ++kActiveIter)
	{
		kActiveIter->second->Update(dDeltaTime);
	}
}

void TargetManager::AddTarget(CharPointer sTargetName, ITarget* pkTarget)
{
	pkTarget->SetName(sTargetName.GetChar());
	m_mpkTargets.insert(std::pair<CharPointer, ITarget*>(sTargetName, pkTarget)); 
}

void TargetManager::AddInstance(ITarget* pkTarget)
{
	pkTarget->SetState(ITarget::INACTIVE);
	m_lpkTargetInstances.push_back(pkTarget); 
}

ITarget* TargetManager::GetTargetType(CharPointer sTargetName)
{
	ASSERT(m_mpkTargets.count(sTargetName))

	return m_mpkTargets.find(sTargetName)->second;
}

void TargetManager::Reset(void)
{
	vuMap<unsigned int, ITarget*>::iterator kIter = m_mpkActiveTargets.begin();

	while (kIter != m_mpkActiveTargets.end())
	{
		kIter->second->Reset();
		kIter->second->GetTargetObject()->setRenderMask(0);
		++kIter;
	}

	m_lpkInactiveTargets.clear();
	m_mpkActiveTargets.clear();
}

//SMB 11 Sep 2023: Show the target before the simulation starts so the
//                 Operator can start tracking it
void TargetManager::ShowTarget(void)
{
	vuList<ITarget*>::iterator kIter = m_lpkTargetInstances.begin();

	for (kIter; kIter != m_lpkTargetInstances.end(); ++kIter)
	{
		m_lpkInactiveTargets.push_back(*kIter);
	}
}

void TargetManager::Start(void)
{
	vuList<ITarget*>::iterator kIter = m_lpkTargetInstances.begin();

	for (kIter; kIter != m_lpkTargetInstances.end(); ++kIter)
	{
		m_lpkInactiveTargets.push_back(*kIter);
	}

	/*  No longer needed - kept for example code
	// Turn off our temporary aiming target if it exists
	m_pkSMBSphere = vpOverlay2DImage::find("SMBSphere");
	if (m_pkSMBSphere) {
		m_pkSMBSphere->setEnable(FALSE);
	}
	*/ 
}

ITarget* TargetManager::GetTargetInstanceByName(const char* sInstanceName)
{
	vuList<ITarget*>::iterator kIter = m_lpkTargetInstances.begin();

	for (kIter; kIter != m_lpkTargetInstances.end(); ++kIter)
	{
		if (! strcmp(sInstanceName, (*kIter)->GetName()))
		{
			return (*kIter);
		}
	}

	return NULL;
}
