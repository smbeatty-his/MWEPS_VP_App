#include <vpFxParticleSystem.h>
#include <AttachedParticleSystem.h>
#include <vpScene.h>
#include <vpObject.h>
#include <ITarget.h>

// SMB WAS: #define NO_END_STATE -1
// Changed to 0 because it's assigned to an unsigned int. this is not used outside this file
#define NO_END_STATE 0


AttachedParticleSystem::AttachedParticleSystem(void) : m_pkSystem(NULL), m_uiEndTargetState(NO_END_STATE), 
													   m_uiEndRegionState(NO_END_STATE)
{

}

AttachedParticleSystem::~AttachedParticleSystem(void)
{
	ASSERT(m_pkSystem)

	m_pkSystem->unref();
}

void AttachedParticleSystem::Activate(vpObject* pkObject)
{
	ASSERT(pkObject)

	Update(pkObject);

	m_pkSystem->setEnable(true);
	(*vpScene::begin())->addChild(m_pkSystem);
}

void AttachedParticleSystem::Update(vpObject* pkObject)
{
	ASSERT(pkObject)

	vuVec3<double> vdRotate;
	pkObject->getRotate(&vdRotate[0], &vdRotate[1], &vdRotate[2]);
	vuMatrix<double> kRotateMat;
	kRotateMat.makeRotate(vdRotate[0], vdRotate[1], vdRotate[2]);
	
	vuVec3<double> vdPos;
	pkObject->getTranslate(&vdPos[0], &vdPos[1], &vdPos[2]);

	vuVec3<double> vdAdjustment = m_vdOffset;
	kRotateMat.transformPoint(&vdAdjustment);
	
	m_pkSystem->setTranslate(vdPos[0] + vdAdjustment[0], vdPos[1] + vdAdjustment[1], vdPos[2] + vdAdjustment[2]);
}

const void AttachedParticleSystem::SetParticleSystem(vpFxParticleSystem* pkSystem)
{
	ASSERT(! m_pkSystem)
	ASSERT(pkSystem)

	m_pkSystem = pkSystem;
	m_pkSystem->ref();
}

bool AttachedParticleSystem::CheckToDeactivate(unsigned int uiTargetState, unsigned int uiRegionState)
{
	if (m_uiEndTargetState <= uiTargetState || m_uiEndRegionState <= uiRegionState)
	{
		m_pkSystem->setEnable(false);
		(*vpScene::begin())->removeChild(m_pkSystem);
		return true;
	}

	return false;
}

void AttachedParticleSystem::InstanceParticleSystem(AttachedParticleSystem* pkSystem)
{
	ASSERT(! m_pkSystem)
	ASSERT(pkSystem)
	ASSERT(pkSystem->GetParticleSystem())

	m_pkSystem = new vpFxParticleSystem();
	m_pkSystem->ref();

	vsgu::copy<vpFxParticleSystem>(m_pkSystem, pkSystem->GetParticleSystem());

	m_vdOffset = pkSystem->GetOffset();
	m_uiEndTargetState = pkSystem->GetTargetEndState();
	m_uiEndRegionState = pkSystem->GetRegionEndState();
}