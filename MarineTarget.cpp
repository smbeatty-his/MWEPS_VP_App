#include <MarineTarget.h>
#include <LoadedObject.h>
#include <vpMarineFxBowWaveAngled.h>
#include <vpMarineFxSternWake.h>
#include <vpMarineFxHullWake.h>
#include <vpMarineShipMotionStrategy.h>
#include <vpMarineShip.h>
#include <vpMarineOceanObserverCentered.h>
#include <vpObject.h>

MarineTarget::MarineTarget(void) : m_pkBowWaveAngled(NULL), m_pkSternWake(NULL), m_pkHullWake(NULL),
								   m_pkMotionStrategy(NULL), m_pkMarineShip(NULL)
{
	
}

MarineTarget::~MarineTarget()
{	
	if (GetClone())
	{
		m_pkBowWaveAngled->unref();
		m_pkSternWake->unref();
		m_pkHullWake->unref();
		m_pkMotionStrategy->unref();
		m_pkMarineShip->unref();
	}
}

int MarineTarget::Configure(void)
{

	return vsgu::SUCCESS;
}

void MarineTarget::Update(const double dTime)
{ 
	ITarget::Update(dTime);
}

void MarineTarget::PopulateTarget(const char* sTargetName)
{
	ASSERT(sTargetName)

	char sLookupName[256];

	strcpy(sLookupName, sTargetName);
	strcat(sLookupName, "Object");
	SetTargetObject(vpObject::find(sLookupName));
	SetName(sTargetName);

	strcpy(sLookupName, sTargetName);
	strcat(sLookupName, "MarineShip");
	m_pkMarineShip = vpMarineShip::find(sLookupName);

	strcpy(sLookupName, sTargetName);
	strcat(sLookupName, "MarineFxBowWaveAngled");
	m_pkBowWaveAngled = vpMarineFxBowWaveAngled::find(sLookupName);

	strcpy(sLookupName, sTargetName);
	strcat(sLookupName, "MarineFxSternWake");
	m_pkSternWake = vpMarineFxSternWake::find(sLookupName);

	strcpy(sLookupName, sTargetName);
	strcat(sLookupName, "MarineFxHullWake");
	m_pkHullWake = vpMarineFxHullWake::find(sLookupName);

	strcpy(sLookupName, sTargetName);
	strcat(sLookupName, "MarineShipMotionStrategy");
	m_pkMotionStrategy = vpMarineShipMotionStrategy::find(sLookupName);

}

void MarineTarget::InstanceTarget(ITarget* pkTarget, const char* sInstanceName)
{
	ASSERT(pkTarget)
	ASSERT(dynamic_cast<MarineTarget*>(pkTarget))
	ASSERT(sInstanceName)

	MarineTarget* pkMarineTarget = (MarineTarget*) pkTarget;

	SetTargetObject(new vpObject());

	vsgu::copy<vpObject>(GetTargetObject(), pkTarget->GetTargetObject());

	GetTargetObject()->setStrategy(NULL);

	SetName(sInstanceName);

	char sName[256];
	
	ASSERT(! m_pkMarineShip)

	strcpy(sName, sInstanceName);
	strcat(sName, "MarineShip");
	m_pkMarineShip = new vpMarineShip();
	m_pkMarineShip->ref();
	m_pkMarineShip->setName(sName);
	CloneShip(pkMarineTarget->GetMarineShip());

	m_pkMarineShip->setOcean(*vpMarineOcean::begin());
	// SMB 25 Jul 2023: since MarineShip is now an attribute, there's no more 1-1 relationship with a Transform
	// WAS: m_pkMarineShip->setTransform(GetTargetObject());
	// Presagis suggested: myObject->insert_attribute(pShipAttribute)
	GetTargetObject()->insert_attribute(m_pkMarineShip);

	ASSERT(! m_pkBowWaveAngled)

	strcpy(sName, sInstanceName);
	strcat(sName, "MarineFxBowWaveAngled");
	m_pkBowWaveAngled = new vpMarineFxBowWaveAngled();
	m_pkBowWaveAngled->ref();
	CloneBowWaveAngled(pkMarineTarget->GetBowWaveAngled());

	m_pkBowWaveAngled->setName(sName);
	m_pkBowWaveAngled->setShip(m_pkMarineShip);
	m_pkBowWaveAngled->setEnable(true);

	ASSERT(! m_pkSternWake)

	strcpy(sName, sInstanceName);
	strcat(sName, "MarineFxSternWake");
	m_pkSternWake = new vpMarineFxSternWake();
	m_pkSternWake->ref();
	CloneSternWake(pkMarineTarget->GetSternWake());
	m_pkSternWake->setName(sName);
	m_pkSternWake->setShip(m_pkMarineShip);
	m_pkSternWake->setEnable(true);

	ASSERT(! m_pkHullWake)

	strcpy(sName, sInstanceName);
	strcat(sName, "MarineFxHullWake");
	m_pkHullWake = new vpMarineFxHullWake();
	m_pkHullWake->ref();
	CloneHullWake(pkMarineTarget->GetHullWake());
	m_pkHullWake->setName(sName);
	m_pkHullWake->setShip(m_pkMarineShip);
	m_pkHullWake->setEnable(true);

	ASSERT(! m_pkMotionStrategy)

	strcpy(sName, sInstanceName);
	strcat(sName, "MarineShipMotionStrategy");
	m_pkMotionStrategy = new vpMarineShipMotionStrategy();
	m_pkMotionStrategy->ref();
	m_pkMotionStrategy->setName(sName);
	CloneMotionStrategy(pkMarineTarget->GetMotionStrategy());
	
	m_pkMotionStrategy->setShip(m_pkMarineShip);

	// SMB 31 Jul 2023 WAS: GetTargetObject()->getStrategy()->setNextStrategy(m_pkMotionStrategy);
	if (NULL == GetTargetObject()->getStrategy()) {
		printf("SMB: GetTargetObject()->getStrategy() returned NULL, using Last Strategy\r\n");
		GetTargetObject()->setLastStrategy(m_pkMotionStrategy); // Suggested by Presagis
	}
	else {
		GetTargetObject()->getStrategy()->setNextStrategy(m_pkMotionStrategy);
	}
	m_pkSternWake->configure();
	m_pkHullWake->configure();
	m_pkBowWaveAngled->configure();

	ITarget::InstanceTarget(pkTarget, sInstanceName);
}

void MarineTarget::CloneShip(vpMarineShip* pkShip)
{
	ASSERT(m_pkMarineShip)
	ASSERT(pkShip)

	m_pkMarineShip->setMaxSpeed( pkShip->getMaxSpeed() );
    m_pkMarineShip->setBeam( pkShip->getBeam() );
    m_pkMarineShip->setWidthAtOrigin( pkShip->getWidthAtOrigin() );
    m_pkMarineShip->setMaxTurnRate( pkShip->getMaxTurnRate() );
    m_pkMarineShip->setBowFlareAngle( pkShip->getBowFlareAngle() );
    m_pkMarineShip->setBowOffset( pkShip->getBowOffset() );
    m_pkMarineShip->setBowWidth( pkShip->getBowWidth() );
    m_pkMarineShip->setBowLength( pkShip->getBowLength() );
    m_pkMarineShip->setBowFreeboard( pkShip->getBowFreeboard() );
    m_pkMarineShip->setBowStempostAngle( pkShip->getBowStempostAngle() );
    m_pkMarineShip->setBowStempostLength( pkShip->getBowStempostLength() );
    m_pkMarineShip->setSternOffset( pkShip->getSternOffset() );
    m_pkMarineShip->setSternWidth( pkShip->getSternWidth() );
    m_pkMarineShip->setSternWakeAngle( pkShip->getSternWakeAngle() );
	m_pkMarineShip->setComputeVelocityEnable(pkShip->getComputeVelocityEnable());
}

void MarineTarget::CloneBowWaveAngled(vpMarineFxBowWaveAngled* pkBowWaveAngled)
{
	ASSERT(m_pkBowWaveAngled)
	ASSERT(pkBowWaveAngled)

	vsgu::copy<vpMarineFxBowWaveAngled>(m_pkBowWaveAngled, pkBowWaveAngled);
}	

void MarineTarget::CloneSternWake(vpMarineFxSternWake* pkSternWake)
{
	ASSERT(m_pkSternWake)
	ASSERT(pkSternWake)

	vsgu::copy<vpMarineFxWake>(m_pkSternWake, pkSternWake);
}

void MarineTarget::CloneHullWake(vpMarineFxHullWake* pkHullWake)
{
	ASSERT(m_pkHullWake)
	ASSERT(pkHullWake)

	vsgu::copy<vpMarineFxWake>(m_pkHullWake, pkHullWake);
}

void MarineTarget::CloneMotionStrategy(vpMarineShipMotionStrategy* pkMotionStrategy)
{
	ASSERT(m_pkMotionStrategy)
	ASSERT(pkMotionStrategy)

	m_pkMotionStrategy->setComputeYawEnable(false);
    m_pkMotionStrategy->setSmoothingFactorPortAndStarboard(pkMotionStrategy->getSmoothingFactorPortAndStarboard());
    m_pkMotionStrategy->setSmoothingFactorBowAndStern(pkMotionStrategy->getSmoothingFactorBowAndStern());
    m_pkMotionStrategy->setPitchFactor(pkMotionStrategy->getPitchFactor());
    m_pkMotionStrategy->setRollFactor(pkMotionStrategy->getRollFactor());
}