#ifndef VIEW_MANAGER_MODULE_H
#define VIEW_MANAGER_MODULE_H

#include <DebugUtil.h>
#include <vuVec3.h>

class ViewManager
{

public:
	
	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new ViewManager();
	}

	static inline ViewManager* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		ASSERT(s_pkInstance)
		delete s_pkInstance;
	}

	void Update(void);
	void Reset(void);
	void Start(void);
	void ChangeObserverPosition(const vuVec3<double>& vdPosition);
	void ChangeObserverFOVSymmetric(const float fHFOV, const float fVFOV);
	void ChangeObserverFOVScale(const double dScale);
	void ChangeObserverFOVSymmetricDiagonal(const float fDiagonal);
	void ChangeObserverFOVAsymmetric(const float fLFOV, const float fRFOV, const float fBFOV, const float fTFOV);

private:

	ViewManager(void);
	~ViewManager(void);

	static ViewManager* s_pkInstance;

};
#endif