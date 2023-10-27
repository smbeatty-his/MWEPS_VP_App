#ifndef OCEAN_MANAGER_MODULE_H
#define OCEAN_MANAGER_MODULE_H

#include <DebugUtil.h>

class OceanManager
{

public:

	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new OceanManager();
	}

	static inline OceanManager* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		delete s_pkInstance;
	}

	void Reset(void);
	void Start(void);
	void SetTideHeight(const float fHeight) const;
	void SetSeaState(const int iSeaState) const;
	void SetDominantWaveDirection(const float fDir) const;
	void SetPeakThreshold(const float fThreshold) const;
	void SetSurfaceWindSpeed(const float fSpeed) const;
	void DisableOcean(void);
	void EnableOcean(void);


private:

	OceanManager(void);
	~OceanManager(void);
	static OceanManager* s_pkInstance;
};

#endif