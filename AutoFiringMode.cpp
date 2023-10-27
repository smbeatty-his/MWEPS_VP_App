#include <AutoFiringMode.h>
#include <BulletManager.h>
#include <GunManager.h>
#include <vpKernel.h>

AutoFiringMode::AutoFiringMode(void) : m_dShotDelayRate(0.016666f), m_dShotDelayAccumTime(0.0f), m_bFiring(false)
{

}

AutoFiringMode::~AutoFiringMode(void)
{

}

void AutoFiringMode::Fire(void)
{
	double dHeading, dPitch;

	vuVec3<double> vdDirPos;

	GunManager::GetInstance()->GetMouseHeadingPitch(&dHeading, &dPitch, &vdDirPos);

	BulletManager::GetInstance()->Fire(vuVec3<double>(dHeading, dPitch, 0.0));

	m_bFiring = true;
}

void AutoFiringMode::Update(double dDeltaTime)
{
	if (m_bFiring && m_dShotDelayAccumTime >= m_dShotDelayRate)
	{
		double dHeading, dPitch;

		vuVec3<double> vdDirPos;

		GunManager::GetInstance()->GetMouseHeadingPitch(&dHeading, &dPitch, &vdDirPos);

		BulletManager::GetInstance()->Fire(vuVec3<double>(dHeading, dPitch, 0.0));
	}

	else
	{
		m_dShotDelayAccumTime += dDeltaTime;
	}
}

void AutoFiringMode::TriggerReleased(void)
{
	m_bFiring = false;
}