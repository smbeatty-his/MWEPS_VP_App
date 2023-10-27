#include <BurstFiringMode.h>
#include <BulletManager.h>
#include <GunManager.h>
#include <vpKernel.h>

BurstFiringMode::BurstFiringMode(void) : m_uiBurstSize(5), m_uiBurstCount(0), m_bFiring(false), 
										 m_dShotDelayRate(0.016666), m_dShotDelayAccumTime(0.0)

{

}

BurstFiringMode::~BurstFiringMode(void)
{

}

void BurstFiringMode::Fire(void)
{
	if (! m_bFiring)
	{
		double dHeading, dPitch;

		vuVec3<double> vdDirPos;

		GunManager::GetInstance()->GetMouseHeadingPitch(&dHeading, &dPitch, &vdDirPos);

		BulletManager::GetInstance()->Fire(vuVec3<double>(dHeading, dPitch, 0.0));

		m_bFiring = true;
	}
}

void BurstFiringMode::Update(double dDeltaTime)
{
	if (m_bFiring && (m_dShotDelayAccumTime >= m_dShotDelayRate))
	{
		++m_uiBurstCount;

		double dHeading, dPitch;

		vuVec3<double> vdDirPos;

		GunManager::GetInstance()->GetMouseHeadingPitch(&dHeading, &dPitch, &vdDirPos);

		BulletManager::GetInstance()->Fire(vuVec3<double>(dHeading, dPitch, 0.0));

		if (m_uiBurstCount >= m_uiBurstSize)
		{
			m_uiBurstCount = 0;
			m_bFiring = false;
		}

		m_dShotDelayAccumTime = 0.0f;
	}
	
	else
	{
		m_dShotDelayAccumTime += dDeltaTime;
	}
}