#include <ViewManager.h>
#include <vpObserver.h>
#include <vpChannel.h>

ViewManager* ViewManager::s_pkInstance = NULL;

ViewManager::ViewManager(void)
{

}

ViewManager::~ViewManager(void)
{

}

void ViewManager::Update(void)
{

}

void ViewManager::Reset(void)
{

}

void ViewManager::Start(void)
{

}

void ViewManager::ChangeObserverPosition(const vuVec3<double> &vdPosition)
{
	(*vpObserver::begin())->setTranslate(vdPosition[0], vdPosition[1], vdPosition[2]);
}

void ViewManager::ChangeObserverFOVSymmetric(const float fHFOV, const float fVFOV)
{
	(*vpObserver::begin())->getChannel(0)->setFOVSymmetric(fHFOV, fVFOV);
}

void ViewManager::ChangeObserverFOVScale(const double dScale)
{
	(*vpObserver::begin())->getChannel(0)->setFOVScale(dScale);
}

void ViewManager::ChangeObserverFOVSymmetricDiagonal(const float fDiagonal)
{
	(*vpObserver::begin())->getChannel(0)->setFOVSymmetricDiagonal(fDiagonal);
}

void ViewManager::ChangeObserverFOVAsymmetric
							(const float fLFOV, const float fRFOV, const float fBFOV, const float fTFOV)
{
	(*vpObserver::begin())->getChannel(0)->setFOVAsymmetric(fLFOV, fRFOV, fBFOV, fTFOV);
}



