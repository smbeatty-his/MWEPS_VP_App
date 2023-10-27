#include <vpObject.h>
#include <vpScene.h>
#include <vpFxParticleSystem.h>
#include <ITarget.h>
#include <vsNode.h>
#include <FactoryManager.h>
#include <AttachedParticleSystem.h>
#include <ParticleSystemManager.h>
#include <SoundManager.h>
#include <IHitRegion.h>
#include <TargetManager.h>
#include <SurfaceType.h>
#include <SteeringController.h>
#include <vpPathWayPointSet.h>
#include <SoundAttachedNode.h>
#include <TargetRecord.h>
#include <vuVec4.h>
#include <vsChannel.h>

#define NUM_THRESHOLDS 4

ITarget::ITarget(void) : m_pkObject(NULL), m_kState(UNSET), m_iPathIndex(PATH_UNSET), m_iWayPointIndex(0),
								m_iStartingPathIndex(PATH_UNSET), m_iStartingWayPointIndex(0), m_bLogStateChange(false)
{
	
}

ITarget::~ITarget()
{

	vuMap<TargetState, vuVector<AttachedParticleSystem*>*>::iterator kIter = m_mpkStateEffectMap.begin();

	for (kIter; kIter != m_mpkStateEffectMap.end(); ++kIter) 
	{
		vuVector<AttachedParticleSystem*>* pkVector = kIter->second;

		while (pkVector->size())
		{
			AttachedParticleSystem* pkSystem = pkVector->back();
			pkVector->pop_back();
			delete pkSystem;
		}

		delete pkVector;
	}

	vuMap<TargetState, vuVector<SoundAttachedNode*>*>::iterator kSoundIter = m_mpkStateSoundMap.begin();

	for (kSoundIter; kSoundIter != m_mpkStateSoundMap.end(); ++kSoundIter)
	{
		vuVector<SoundAttachedNode*>* pkVector = kSoundIter->second;

		while (pkVector->size())
		{		
			SoundAttachedNode* pkSound = pkVector->back();
			m_pkObject->removeChild(pkSound);
			pkVector->pop_back();
			delete pkSound;
		}

		delete pkVector;
	}

	vuMap<CharPointer, IHitRegion*>::iterator kRegionIter = m_mpkRegionMap.begin();

	for (kRegionIter; kRegionIter != m_mpkRegionMap.end(); ++kRegionIter)
	{
		delete kRegionIter->second;
	}

	ClearTargetRecords();

	delete m_pkSteeringController;
}

void ITarget::SetName(const char* sName)
{
	m_pkObject->setName(sName);
}

const char* ITarget::GetName(void) const
{
	return m_pkObject->getName();
}

void ITarget::ProcessHit(const char* sRegionName, const vuVec3<double>& vdHitPos)
{
	ASSERT(sRegionName)
	ASSERT(m_mpkRegionMap.count(sRegionName))

	printf("\nRegion Name: %s\n", sRegionName);

	IHitRegion* pkRegion = m_mpkRegionMap.find(sRegionName)->second;

	SurfaceType* pkSurface = TargetManager::GetInstance()->GetSurfaceType(pkRegion->GetSurfaceType());

	ParticleSystemManager::GetInstance()->AddParticleSystem(pkSurface->GetEffectName(), vdHitPos);

	SoundManager::GetInstance()->PlayEnviromentalSound(pkSurface->GetSoundName(), vdHitPos);

	int iHPChange = pkRegion->ProcessHit(this);

	m_iHitPoints -= iHPChange;

	ASSERT(m_kState >= 2)

	TargetState kInitialState = m_kState;

	// SMB Local variable never used
	//int iHP = m_aiHpThresholds[((int) m_kState) - 2];

	while (m_iHitPoints <= m_aiHpThresholds[m_kState - 2] && m_kState < ITarget::DESTROYING)
	{
		m_kState = (TargetState) (m_kState + 1);
	}

	if (kInitialState - m_kState)
	{
		ProcessStateChange();
		m_bLogStateChange = true;
	}

	printf("Target HPs = %d\nTarget State = %d\n\n", m_iHitPoints, m_kState);
}

void ITarget::InstanceTarget(ITarget *pkTarget, const char *sInstanceName)
{
	vuMap<TargetState, vuVector<AttachedParticleSystem*>*>::const_iterator kVectorIter 
														= pkTarget->GetEffectMap().begin();
	for (kVectorIter; kVectorIter != pkTarget->GetEffectMap().end(); ++kVectorIter)
	{
		vuVector<AttachedParticleSystem*>* pkVector = new vuVector<AttachedParticleSystem*>();

		vuVector<AttachedParticleSystem*>::const_iterator kEffectIter = kVectorIter->second->begin();

		for (kEffectIter; kEffectIter != kVectorIter->second->end(); ++kEffectIter)
		{
			AttachedParticleSystem* pkSystem = new AttachedParticleSystem();
			pkSystem->InstanceParticleSystem(*kEffectIter);
			pkVector->push_back(pkSystem);
		}

		m_mpkStateEffectMap.insert(std::pair<TargetState, vuVector<AttachedParticleSystem*>*>
											(kVectorIter->first, pkVector));
	}

	vuMap<TargetState, vuVector<SoundAttachedNode*>*>::const_iterator kSoundIter = pkTarget->GetSoundMap().begin();

	for (kSoundIter; kSoundIter != pkTarget->GetSoundMap().end(); ++kSoundIter)
	{
		vuVector<SoundAttachedNode*>* pkVector = new vuVector<SoundAttachedNode*>();

		vuVector<SoundAttachedNode*>::const_iterator kSoundVecIter = kSoundIter->second->begin();
		
		for (kSoundVecIter; kSoundVecIter != kSoundIter->second->end(); ++kSoundVecIter)
		{
			SoundAttachedNode* pkSound = (SoundAttachedNode*) 
										   FactoryManager::GetInstance()->CreateSound((*kSoundVecIter)->GetClassType());
			
			pkSound->CloneSound(*kSoundVecIter);
			pkVector->push_back(pkSound);
		}
	}

	vuMap<CharPointer, IHitRegion*>::const_iterator kRegionIter = pkTarget->GetRegionMap().begin();

	for (kRegionIter; kRegionIter != pkTarget->GetRegionMap().end(); ++kRegionIter)
	{
		IHitRegion* pkRegion = FactoryManager::GetInstance()->CreateHitRegion(kRegionIter->second->GetClassName());
		pkRegion->InstanceHitRegion(kRegionIter->second);
		AddHitRegion(kRegionIter->first, pkRegion);
	}

	for (int i = 0; i < NUM_THRESHOLDS; ++i)
	{
		m_aiHpThresholds[i] = pkTarget->m_aiHpThresholds[i];
	}

	m_iHitPoints = pkTarget->GetHitPoints();
	m_iStartingHitPoints = pkTarget->GetStartingHitPoints();
	m_iHitDecrement = pkTarget->GetHitDecrement();
	m_dMaxSpeed = pkTarget->GetMaxSpeed();
	m_dMaxForce = pkTarget->GetMaxForce();
	m_dDecelerationRate = pkTarget->GetDecelerationRate();
	m_vdCenterOfMassOffset = pkTarget->GetCenterOfMassOffset();

	MarkAsClone();
}

const void ITarget::AddAttachedParticleSystem(AttachedParticleSystem* pkSystem)
{
	m_lpkAttachedEffects.push_back(pkSystem);
}

const void ITarget::RemoveAttachedParticleSystem(AttachedParticleSystem* pkSystem)
{
	vuList<AttachedParticleSystem*>::iterator kIter = m_lpkAttachedEffects.begin();
	
	while (kIter != m_lpkAttachedEffects.end())
	{
		if (pkSystem == *kIter)
		{
			kIter = m_lpkAttachedEffects.erase(kIter);
			kIter = m_lpkAttachedEffects.end();
		}
		else
		{
			++kIter;
		}
	}
}

const void ITarget::AddAttachedSound(SoundAttachedNode* pkSound)
{
	m_lpkAttachedSounds.push_back(pkSound);
}

void ITarget::Update(const double dTime)
{
	vuVec3<double> vdPrevPos;
	GetTargetObject()->getTranslate(&(vdPrevPos[0]), &(vdPrevPos[1]), &(vdPrevPos[2]));
	
	vuVec3<double> vdPrevOrient;
	GetTargetObject()->getOrientation(&(vdPrevOrient[0]), &(vdPrevOrient[1]), &(vdPrevOrient[2]));
	
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

void ITarget::UpdateVelocity(const double dTime)
{
	vuVec3<double> vdAcceleration = m_pkSteeringController->Calculate(this);

	m_vdVelocity += vdAcceleration * dTime;

	if (m_vdVelocity.length() > m_dMaxSpeed)
	{
		m_vdVelocity.normalize();
		m_vdVelocity *= m_dMaxSpeed; 
	}

	vuVec3<double> vdUnitVel = m_vdVelocity;
	vdUnitVel.normalize();

	double dAngle = acos(vdUnitVel.dot(vuVec3<double>::unitY)) * _180_OVER_PI;
	
	vuVec3<double> vdCross;
	vdCross.cross(vdUnitVel, vuVec3<double>::unitY);

	if (vdCross[2] < 0)
	{
		m_pkObject->setRotate(abs(dAngle), 0.0, 0.0);
	}

	else
	{
		m_pkObject->setRotate(-abs(dAngle), 0.0, 0.0);
	}
}

void ITarget::UpdateTranslate(const double dTime)
{
	vuVec3<double> vdTranslate;
	GetTargetObject()->getTranslate(&(vdTranslate[0]), &(vdTranslate[1]), &(vdTranslate[2]));
	vdTranslate += m_vdVelocity * dTime;
	GetTargetObject()->setTranslate(vdTranslate[0], vdTranslate[1], 0.0);
}

void ITarget::Reset(void)
{
	m_iHitPoints = m_iStartingHitPoints;
	m_kState = ITarget::INACTIVE;
	m_iPathIndex = m_iStartingPathIndex;
	m_iWayPointIndex = m_iStartingWayPointIndex;

	vuMap<CharPointer, IHitRegion*>::iterator kIter = m_mpkRegionMap.begin();

	for (kIter; kIter != m_mpkRegionMap.end(); ++kIter)
	{
		kIter->second->Reset();
	}
	
	vuList<AttachedParticleSystem*>::iterator kEffectsIter = m_lpkAttachedEffects.begin();

	for (kEffectsIter; kEffectsIter != m_lpkAttachedEffects.end(); ++kEffectsIter)
	{
		(*kEffectsIter)->GetParticleSystem()->setEnable(false);
		(*vpScene::begin())->removeChild((*kEffectsIter)->GetParticleSystem());
	}

	m_pkObject->setTranslate(m_vfStartPosition[0], m_vfStartPosition[1], m_vfStartPosition[2]);
	m_pkObject->setRotate(m_vfStartRotation[0], m_vfStartRotation[1], m_vfStartRotation[2]);

	m_lpkAttachedEffects.clear();
}

void ITarget::AddSteeringBehavior(ISteeringBehavior* pkBehavior)
{
	m_pkSteeringController->AddSteeringBehavior(pkBehavior);
}

void ITarget::ProcessStateChange(void)
{
	if (m_mpkStateEffectMap.count(m_kState))
	{
		vuVector<AttachedParticleSystem*>* pkVector = m_mpkStateEffectMap.find(m_kState)->second;
	
		vuVector<AttachedParticleSystem*>::iterator kIter = pkVector->begin();

		for (kIter; kIter != pkVector->end(); ++kIter)
		{
			AttachedParticleSystem* pkSystem = *kIter;
			pkSystem->Activate(m_pkObject);
			AddAttachedParticleSystem(pkSystem);
		}
	}

	if (m_mpkStateSoundMap.count(m_kState))
	{
		vuVector<SoundAttachedNode*>* pkVector = m_mpkStateSoundMap.find(m_kState)->second;
	
		vuVector<SoundAttachedNode*>::iterator kIter = pkVector->begin();

		for (kIter; kIter != pkVector->end(); ++kIter)
		{
			SoundAttachedNode* pkSound = *kIter;
			pkSound->Activate(m_pkObject);
			AddAttachedSound(pkSound);
		}
	}

	vuList<AttachedParticleSystem*>::iterator kEffectsIter = m_lpkAttachedEffects.begin();

	while (kEffectsIter != m_lpkAttachedEffects.end())
	{
		if ((*kEffectsIter)->CheckToDeactivate((unsigned int) m_kState, (unsigned int) IHitRegion::UNSET))
		{
			m_lpkAttachedEffects.erase(kEffectsIter);
		}
		else
		{
			++kEffectsIter;
		}	
	}

	vuList<SoundAttachedNode*>::iterator kSoundIter = m_lpkAttachedSounds.begin();

	while (kSoundIter != m_lpkAttachedSounds.end())
	{
		if ((*kSoundIter)->GetEndState() <= m_kState)
		{
			m_lpkAttachedSounds.erase(kSoundIter);
		}
		else
		{
			++kSoundIter;
		}	
	}
}

void ITarget::UpdateTargetRecord(void)
{
	TargetRecord* pkRecord = new TargetRecord();

	pkRecord->SetTime(vpKernel::instance()->getSimulationTime());
	pkRecord->SetState(GetState());
	vuVec3<double> vdTemp;
	GetTargetObject()->getTranslate(&(vdTemp[0]), &(vdTemp[1]), &(vdTemp[2]));
	pkRecord->SetPosition(vdTemp);
	GetTargetObject()->getOrientation(&(vdTemp[0]), &(vdTemp[1]), &(vdTemp[2]));
	pkRecord->SetRotation(vdTemp);
	pkRecord->SetCenterOfMass(GetCenterOfMass());
	pkRecord->SetCOMScreenCoordinates(GetCOMScreenCoordinates(pkRecord->GetCenterOfMass()));

	vuMap<CharPointer, IHitRegion*>::const_iterator kIter = m_mpkRegionMap.begin();

	for (kIter; kIter != m_mpkRegionMap.end(); ++kIter)
	{
		pkRecord->AddRegionState(kIter->second->GetState());
	}

	m_lpkTargetRecords.push_back(pkRecord);
}

void ITarget::ClearTargetRecords(void)
{
	while (m_lpkTargetRecords.size())
	{
		TargetRecord* pkRecord = m_lpkTargetRecords.back();
		m_lpkTargetRecords.pop_back();
		delete pkRecord;
	}
}

const vuVec3<double> ITarget::GetCenterOfMass(void) const
{
	ASSERT(GetTargetObject())

	if ((! m_vdCenterOfMassOffset[0]) && (! m_vdCenterOfMassOffset[1]) && (! m_vdCenterOfMassOffset[2]))
	{
		vuVec3<double> vdPosition;
		GetTargetObject()->getTranslate(&(vdPosition[0]), &(vdPosition[1]), &(vdPosition[2]));
		return (vdPosition + m_vdCenterOfMassOffset);
	}

	else
	{
		vuVec3<double> vdRotate;
		GetTargetObject()->getRotate(&vdRotate[0], &vdRotate[1], &vdRotate[2]);
		vuMatrix<double> kRotateMat;
		kRotateMat.makeRotate(vdRotate[0], vdRotate[1], vdRotate[2]);
	
		vuVec3<double> vdPosition;
		GetTargetObject()->getTranslate(&vdPosition[0], &vdPosition[1], &vdPosition[2]);

		vuVec3<double> vdAdjustment = m_vdCenterOfMassOffset;
		kRotateMat.transformPoint(&vdAdjustment);

		return (vdAdjustment + vdPosition);
	}
}

const vuVec2<double> ITarget::GetCOMScreenCoordinates(const vuVec3<double>& vdCenterOfMass) const
{
// SMB 26 Jul 2023 WAS:	vuVec4<float>& vdCOMPoint = vuVec4<float>((float)vdCenterOfMass[0], (float)vdCenterOfMass[1],
//		(float)vdCenterOfMass[2], 1.0f);
// Removed "&" to avoid non-const reference can only be bound to an lvalue error

	vuVec4<float> vdCOMPoint = vuVec4<float>((float)vdCenterOfMass[0], (float)vdCenterOfMass[1],
											  (float)vdCenterOfMass[2], 1.0f);

	(*vsChannel::begin())->getVrChannel()->getWorldToScreenMatrix().transform(&vdCOMPoint);

	// divide by w
    double dX = vdCOMPoint[0]/vdCOMPoint[3]; // x between [-1,1]
    double dY = vdCOMPoint[1]/vdCOMPoint[3]; // y between [-1,1]

    // normalize to [0,1] range
    dX = (dX + 1.0f) / 2.0f;
    dY = (dY + 1.0f) / 2.0f;
	
	return vuVec2<double>(dX, dY);
}