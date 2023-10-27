#include <AARManager.h>
#include <BulletManager.h>
#include <ParticleSystemManager.h>

AARManager* AARManager::s_pkInstance = NULL;

AARManager::AARManager()
{
	m_bReviewActive = false;
}

AARManager::~AARManager()
{

}

void AARManager::Shutdown(void)
{
	delete s_pkInstance;
}

void AARManager::Update(void)
{

}