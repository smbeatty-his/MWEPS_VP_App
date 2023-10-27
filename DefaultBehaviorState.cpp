#include <DefaultBehaviorState.h>
#include <ITarget.h>
#include <AttachedParticleSystem.h>
#include <SoundAttachedNode.h>

DefaultBehaviorState* DefaultBehaviorState::s_pkInstance = NULL;

DefaultBehaviorState::DefaultBehaviorState(void)
{
	
}

DefaultBehaviorState::~DefaultBehaviorState(void)
{
	
}	

void DefaultBehaviorState::Update(const double dTime, ITarget* pkTarget)
{
	if (pkTarget->GetState() < ITarget::DESTROYING)
	{
		pkTarget->UpdateVelocity(dTime);
		pkTarget->UpdateTranslate(dTime);

		vuVec3<double> vdPos;
		pkTarget->GetTargetObject()->getPosition(&(vdPos[0]), &(vdPos[1]), &(vdPos[2]));

		vuList<AttachedParticleSystem*>::iterator kIter = pkTarget->GetAttachedParticleSystems().begin();

		for (kIter; kIter != pkTarget->GetAttachedParticleSystems().end(); ++kIter)
		{
			(*kIter)->Update(pkTarget->GetTargetObject());
		}

		vuList<SoundAttachedNode*>::iterator kSoundIter = pkTarget->GetAttachedSounds().begin();

		for (kSoundIter; kSoundIter != pkTarget->GetAttachedSounds().end(); ++kSoundIter)
		{
			(*kIter)->Update(pkTarget->GetTargetObject());
		}
	}
}

void DefaultBehaviorState::OnStateEntry(ITarget* pkTarget)
{

}

void DefaultBehaviorState::OnStateExit(ITarget* pkTarget)
{

}