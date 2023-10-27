#ifndef MARINE_STEERING_TARGET_MODULE_H
#define MARINE_STEERING_TARGET_MODULE_H

#include <SteeringTarget.h>
#include <DebugUtil.h>
#include <vpMarineShip.h>

class vpMarineFxBowWaveAngled;
class vpMarineFxSternWake;
class vpMarineFxHullWake;
class vpMarineShipMotionStrategy;
//SMB 07 Jul 2023 - remove class vpMarineShip - has been replaced by vpMarineShipAttribute
//class vpMarineShip;
//class vpMarineShipAttribute;
class vsNode;

class MarineSteeringTarget : public SteeringTarget
{

public:

	virtual ~MarineSteeringTarget(void);
	virtual int Configure(void);
	virtual void Update(const double dTime);
	virtual void PopulateTarget(const char* sTargetName);
	virtual void InstanceTarget(ITarget* pkTarget, const char* sInstanceName);
	virtual inline const char* GetClassname(void) const { return "MarineSteeringTarget"; }

	inline vpMarineFxBowWaveAngled* GetBowWaveAngled(void) const { return m_pkBowWaveAngled; }
	const inline void SetBowWaveAngled(vpMarineFxBowWaveAngled* pkBowWaveAngled) 
															{ m_pkBowWaveAngled = pkBowWaveAngled; }
	
	inline vpMarineFxSternWake* GetSternWake(void) const { return m_pkSternWake; }
	const inline void SetSternWake(vpMarineFxSternWake* pkSternWake) { m_pkSternWake = pkSternWake; }
	
	inline vpMarineFxHullWake* GetHullWake(void) const { return m_pkHullWake; }
	const inline void SetHullWake(vpMarineFxHullWake* pkHullWake) { m_pkHullWake = pkHullWake; }
	
	inline vpMarineShipMotionStrategy* GetMotionStrategy(void) const { return m_pkMotionStrategy; }
	const inline void SetMotionStrategy(vpMarineShipMotionStrategy* pkMotionStrategy) 
															{ m_pkMotionStrategy = pkMotionStrategy; }
	
	inline vpMarineShip* GetMarineShip(void) const { return m_pkMarineShip; }
	const inline void SetMarineShip(vpMarineShip* pkMarineShip) { m_pkMarineShip = pkMarineShip; }

	ConcreteFactory(ITarget, MarineSteeringTarget)

protected:
	
	MarineSteeringTarget(void);

private:

	
	void CloneShip(vpMarineShip* pkTarget);
	void CloneBowWaveAngled(vpMarineFxBowWaveAngled* pkTarget);
	void CloneSternWake(vpMarineFxSternWake* pkTarget);
	void CloneHullWake(vpMarineFxHullWake* pkTarget);
	void CloneMotionStrategy(vpMarineShipMotionStrategy* pkTarget);
	
	vpMarineFxBowWaveAngled* m_pkBowWaveAngled;
	vpMarineFxSternWake* m_pkSternWake;
	vpMarineFxHullWake* m_pkHullWake;
	vpMarineShipMotionStrategy* m_pkMotionStrategy;
	vpMarineShip* m_pkMarineShip;
	vuVec3<double> m_vdTargetedPoint;
};

typedef MarineSteeringTarget::MarineSteeringTargetFactory MarineSteeringTargetFactory;

#endif