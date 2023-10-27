#include <OceanManager.h>
#include <vpMarineOcean.h>

OceanManager* OceanManager::s_pkInstance = NULL;

OceanManager::OceanManager(void)
{
	(*vpMarineOcean::begin())->getWaveGenerator()->setFreezeEnable(true);
}

OceanManager::~OceanManager(void)
{

}

void OceanManager::Reset(void)
{

}

void OceanManager::Start(void)
{

}

void OceanManager::SetTideHeight(const float fHeight) const
{
	(*vpMarineOcean::begin())->setTideHeight(fHeight);
}

void OceanManager::SetSeaState(const int iSeaState) const
{
	(*vpMarineOcean::begin())->getWaveGenerator()->setSeaState(iSeaState);
}

void OceanManager::SetDominantWaveDirection(const float fDir) const
{
	(*vpMarineOcean::begin())->getWaveGenerator()->setDominantWaveDirection(fDir);
}

void OceanManager::SetPeakThreshold(const float fThreshold) const
{
	(*vpMarineOcean::begin())->getWaveGenerator()->setPeakThreshold(fThreshold);
}

void OceanManager::SetSurfaceWindSpeed(const float fSpeed) const
{
	(*vpMarineOcean::begin())->getWaveGenerator()->setSurfaceWindSpeed(fSpeed);
}

void OceanManager::DisableOcean(void)
{
	(*vpMarineOcean::begin())->getWaveGenerator()->setFreezeEnable(true);
}

void OceanManager::EnableOcean(void)
{
	(*vpMarineOcean::begin())->getWaveGenerator()->setFreezeEnable(false);
}


