#ifndef TARGET_MANAGER_MODULE_H
#define TARGET_MANAGER_MODULE_H

#include <DebugUtil.h>
#include <vuMap.h>
#include <vuList.h>
#include <CharPointer.h>

class ITarget;
class SurfaceType;
class vpOverlay2DImage;

class TargetManager
{
public:

	static inline TargetManager* GetInstance(void) 
	{ 
		ASSERT(s_pkInstance)
		return s_pkInstance; 
	}
	static inline void Initialize(int iPulseRate = 10)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new TargetManager(iPulseRate);
	}
	static inline void Shutdown(void)
	{
		delete s_pkInstance;
	}

	void Update(double dSimTime, double dDeltaTime);
	void Reset(void);
	void Start(void);

	void AddTarget(CharPointer sTargetName, ITarget* pkTarget);
	// SMB 11 Sep 2023 added the following to display target before Simulation starts
	void TargetManager::ShowTarget(void);
	ITarget* GetTargetType(CharPointer sTargetName);
	void AddInstance(ITarget* pkTarget);
	const inline unsigned int GetNumTargetInstances(void) const { return m_lpkTargetInstances.size(); }
	const inline vuList<ITarget*>& GetTargetInstanceList(void) const { return m_lpkTargetInstances; }
	ITarget* GetTargetInstanceByName(const char* sInstanceName);

	inline ITarget* GetActiveTarget(unsigned int uiTarget) const
	{
		ASSERT(m_mpkActiveTargets.count(uiTarget))
		ASSERT(m_mpkActiveTargets.find(uiTarget)->second)

		return m_mpkActiveTargets.find(uiTarget)->second;
	}

	inline SurfaceType* GetSurfaceType(CharPointer sName)
	{
		ASSERT(m_mpkSurfaceTypes.count(sName))
		ASSERT(m_mpkSurfaceTypes.find(sName)->second)

		return m_mpkSurfaceTypes.find(sName)->second;
	}

	const inline void AddSurfaceType(CharPointer sName, SurfaceType* pkType)
	{
		m_mpkSurfaceTypes.insert(std::pair<CharPointer, SurfaceType*>(sName, pkType));
	}


private:

	TargetManager(int iPulseRate);
	~TargetManager();

	int m_iTargetPulseRate;
	double m_dTargetPulseDelay;
	double m_dTargetDelayedTime;
	static TargetManager* s_pkInstance;
	vuMap<CharPointer, ITarget*> m_mpkTargets;
	vuList<ITarget*> m_lpkTargetInstances;
	vuMap<CharPointer, SurfaceType*> m_mpkSurfaceTypes;
	vuMap<unsigned int, ITarget*> m_mpkActiveTargets;
	vuList<ITarget*> m_lpkInactiveTargets;
// SMB: not needed, kept for example code
// public:
//	vpOverlay2DImage* m_pkSMBSphere;

};

#endif