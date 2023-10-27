#include <WeatherManager.h>
#include <vpEnv.h>
#include <vpEnvWind.h>
#include <vpEnvRain.h>
#include <vpEnvSnow.h>
#include <vpEnvCloudLayer.h>

WeatherManager* WeatherManager::s_pkInstance = NULL;

WeatherManager::WeatherManager(void)
{

}

WeatherManager::~WeatherManager(void)
{

}

void WeatherManager::SetTime(const float fTime, const int iDay, const int iMonth, const int iYear) const
{
	vpEnv* pkEnv = *vpEnv::begin();

	pkEnv->setDate(iDay, iMonth, iYear);
	pkEnv->setTimeOfDay(fTime);
}

void WeatherManager::SetReferencePosition(const float fLongitude, const float fLatitude) const
{
	(*vpEnv::begin())->setReferencePosition(fLongitude, fLatitude);
}

void WeatherManager::SetWind(const float fSpeed, const vuVec3<float>& vfDir) const
{
	vpEnvWind* pkWind = *vpEnvWind::begin();
	pkWind->setSpeed(fSpeed);
	pkWind->setDirection(vfDir[0], vfDir[1], vfDir[2]);
}

void WeatherManager::SetWeather(const WeatherState kWeatherState)
{
	switch (kWeatherState)
	{
		case CLEAR:
		{
			SetWeatherClear();
			break;
		}

		case LIGHT_RAIN:
		{
			SetWeatherLightRain();
			break;
		}

		case MEDIUM_RAIN:
		{
			SetWeatherMediumRain();
			break;
		}

		case HEAVY_RAIN:
		{
			SetWeatherHeavyRain();
			break;
		}

		case LIGHT_SNOW:
		{
			SetWeatherLightSnow();
			break;
		}

		case MEDIUM_SNOW:
		{
			SetWeatherMediumSnow();
			break;
		}

		case HEAVY_SNOW:
		{
			SetWeatherHeavySnow();
			break;
		}

	}
}

void WeatherManager::SetWeatherClear(void)
{
	(*vpEnvRain::begin())->setEnable(false);
	(*vpEnvSnow::begin())->setEnable(false);
	(*vpEnvCloudLayer::begin())->setCoverageScale(0.0f);
}

void WeatherManager::SetWeatherLightRain(void)
{
	vpEnvRain* pkRain = *vpEnvRain::begin();
	(*vpEnvSnow::begin())->setEnable(false);
	pkRain->setNumParticles(5000);
	pkRain->setEnable(true);
	(*vpEnvCloudLayer::begin())->setCoverageScale(0.2f);
}

void WeatherManager::SetWeatherMediumRain(void)
{
	vpEnvRain* pkRain = *vpEnvRain::begin();
	(*vpEnvSnow::begin())->setEnable(false);
	pkRain->setNumParticles(20000);
	pkRain->setEnable(true);
	(*vpEnvCloudLayer::begin())->setCoverageScale(0.65f);
}

void WeatherManager::SetWeatherHeavyRain(void)
{
	vpEnvRain* pkRain = *vpEnvRain::begin();
	(*vpEnvSnow::begin())->setEnable(false);
	pkRain->setNumParticles(50000);
	pkRain->setEnable(true);
	(*vpEnvCloudLayer::begin())->setCoverageScale(1.0f);
}

void WeatherManager::SetWeatherLightSnow(void)
{
	vpEnvSnow* pkSnow = *vpEnvSnow::begin();
	(*vpEnvRain::begin())->setEnable(false);
	pkSnow->setNumParticles(5000);
	pkSnow->setEnable(true);
	(*vpEnvCloudLayer::begin())->setCoverageScale(0.2f);
}

void WeatherManager::SetWeatherMediumSnow(void)
{
	vpEnvSnow* pkSnow = *vpEnvSnow::begin();
	(*vpEnvRain::begin())->setEnable(false);
	pkSnow->setNumParticles(20000);
	pkSnow->setEnable(true);
	(*vpEnvCloudLayer::begin())->setCoverageScale(0.65f);
}

void WeatherManager::SetWeatherHeavySnow(void)
{
	vpEnvSnow* pkSnow = *vpEnvSnow::begin();
	(*vpEnvRain::begin())->setEnable(false);
	pkSnow->setNumParticles(50000);
	pkSnow->setEnable(true);
	(*vpEnvCloudLayer::begin())->setCoverageScale(1.0f);
}



