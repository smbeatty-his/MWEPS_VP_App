#include <SingleShotFiringMode.h>
#include <BulletManager.h>
#include <GunManager.h>

void SingleShotFiringMode::Fire(void)
{
	BulletManager::GetInstance()->Fire();
}

void SingleShotFiringMode::Update(double dDeltaTime)
{

}