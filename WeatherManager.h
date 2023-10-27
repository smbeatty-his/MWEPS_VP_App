#ifndef WEATHER_MANAGER_MODULE_H
#define WEATHER_MANAGER_MODULE_H

#include <DebugUtil.h>
#include <vuVec3.h>

class WeatherManager
{

public:

	enum WeatherState
	{
		UNSET,
		CLEAR,
		LIGHT_RAIN,
		MEDIUM_RAIN,
		HEAVY_RAIN,
		LIGHT_SNOW,
		MEDIUM_SNOW,
		HEAVY_SNOW,
		INVALID
	};

	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new WeatherManager();
	}

	static inline WeatherManager* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		ASSERT(s_pkInstance)
		delete s_pkInstance;
	}

	void SetTime(const float fTime, const int iDay, const int iMonth, const int iYear) const;
	void SetReferencePosition(const float dLongitude, const float dLatitude) const;
	void SetWind(const float fSpeed, const vuVec3<float>& vfDir) const;
	void SetWeather(const WeatherState kWeatherState);
	void SetWeatherClear(void);
	void SetWeatherLightRain(void);
	void SetWeatherMediumRain(void);
	void SetWeatherHeavyRain(void);
	void SetWeatherLightSnow(void);
	void SetWeatherMediumSnow(void);
	void SetWeatherHeavySnow(void);

private:

	WeatherManager(void);
	~WeatherManager(void);

	static WeatherManager* s_pkInstance;
};

#endif