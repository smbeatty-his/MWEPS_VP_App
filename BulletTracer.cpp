#include <vuAllocTracer.h>
#include <vrGeometry.h>
#include <vrLight.h>
#include <vrMode.h>
#include <vrState.h>
#include <vsDOF.h>
#include <vsGeometry.h>
#include <vsRenderStrategy.h>
#include <vsTransform.h>
#include <vpApp.h>
#include <vpObject.h>
#include <vpFxSplash.h>
#include <BulletManager.h>
#include <ParticleSystemManager.h>
#include <BulletRecord.h>
#include <DebugUtil.h>

#define INITIAL_TRACER_VELOCITY vuVec3<double> (0.0, 1000.0, 0.0);
#define ISECTOR_MASK 0xFFFFFFFF
#define WATER_OBJECT "OceanObserverCentered"
#define SPLASH_OBJECT "Splash"
#define WATER_EFFECT_END_TIME 5.0f

BulletManager* BulletManager::s_pkInstance = NULL;
bool BulletManager::s_bDrawTracers = false;

BulletManager::BulletManager() 
{ 
	s_bDrawTracers = true;
	ASSERT(Configure();)
}

BulletManager::~BulletManager(void)
{
	m_pkGeometry->setRenderStrategy(NULL);
    m_pkRenderStrategy->unref();
    m_pkGeometry->unref();
    m_pkBulletNode->unref();

	while (m_lpkAvailableBullets.size())
	{
		BulletTracer* pkTracer = m_lpkAvailableBullets.back();
		m_lpkAvailableBullets.pop_back();
		delete pkTracer;
	}

	while (m_lpkActiveBullets.size())
	{
		BulletTracer* pkTracer = m_lpkActiveBullets.back();
		m_lpkActiveBullets.pop_back();
		delete pkTracer;
	}

	while (m_lpkExpiredBullets.size())
	{
		BulletRecord* pkRecord = m_lpkExpiredBullets.back();
		m_lpkExpiredBullets.pop_back();
		delete pkRecord;
	}
}

void BulletManager::Shutdown(void)
{
	delete s_pkInstance;
}

BulletManager::BulletTracer::BulletTracer(void)
{
	Configure();
}

BulletManager::BulletTracer::~BulletTracer(void)
{
	m_pkBulletNode->unref();
	m_pkGeometry->unref();
	m_pkRenderStrategy->unref();
	m_isector->unref();
	delete m_pkRecord;
}

bool BulletManager::BulletTracer::Update(const double& dTime)
{
	const double dGravity = -9.8;

	m_pkRecord->AddPoint(&m_vdPosition);
	m_vdVelocity[2] += dGravity * dTime;

	m_isector->setPosition(m_vdPosition[0], m_vdPosition[1], m_vdPosition[2]);

	m_vdPosition += (m_vdVelocity + BulletManager::GetInstance()->GetWindVelocity()) * dTime;
		
	vuVec3<double> vdDistTraveled;
	m_isector->getPosition(&(vdDistTraveled[0]), &(vdDistTraveled[1]), &(vdDistTraveled[2]));

	vdDistTraveled[0] = m_vdPosition[0] - vdDistTraveled[0];
	vdDistTraveled[1] = m_vdPosition[1] - vdDistTraveled[1];
	vdDistTraveled[2] = m_vdPosition[2] - vdDistTraveled[2];

	double dHeading = vuRad2Deg(-vuArcTan(vdDistTraveled[0], vdDistTraveled[1]));
	double dPitch = vuRad2Deg(vuArcTan(vdDistTraveled[2], 
							vuSqrt(vuSq(vdDistTraveled[0]) + vuSq(vdDistTraveled[1]))));

	m_isector->setRotate(dHeading, dPitch, 0.0);
	m_isector->setSegmentRange(vdDistTraveled.length());
	m_isector->update();

	if (m_isector->getHit())
	{
		vpObject* pkObject = m_isector->getHitObject();
		if (pkObject)
		{
			printf("Hit Object %s\n", pkObject->getName());
		}
		else
		{
			vsNode* pkNode = m_isector->getHitNode();
			if (pkNode)
			{
				printf("Hit Node %s\n", pkNode->getName());
				if (! strcmp(pkNode->getName(), WATER_OBJECT)
					|| ! strcmp(pkNode->getName(), SPLASH_OBJECT))
				{
					vpFxSplash* pkSplash = new vpFxSplash();
					pkSplash->configure();
					m_isector->getHitPoint(&m_vdPosition);
					pkSplash->setTranslate(m_vdPosition[0], m_vdPosition[1], m_vdPosition[2]);
					pkSplash->setName("Splash");
					pkSplash->setEnable(true);
					pkSplash->setScale(0.25, 0.25, 0.25);							
					pkSplash->ref();
					ParticleSystemManager::GetInstance()->AddParticleSystem(pkSplash);
					(*vpScene::begin())->push_back_child(pkSplash);
				}
			}
		}
		
		m_pkRecord->AddPoint(&m_vdPosition);
		BulletManager::GetInstance()->AddExpiredBullet(m_pkRecord);
		m_pkRecord = new BulletRecord();

		return true;
	}
    
	else 
	{
		vuVec3<float>* pvfVertex = m_pkGeometry->getVertices();
        pvfVertex[0].set(m_vdPosition[0], m_vdPosition[1], m_vdPosition[2]);

		m_pkGeometry->setNumPrimitives(1);
		m_pkGeometry->setVertices(pvfVertex);
		m_pkRenderStrategy->update();

		// update our bounding sphere
		m_pkBulletNode->dirtyUp(vsNode::DIRTY_BOUNDS);
		m_pkBulletNode->setRenderMask(0xffffffff);

		return false;
    }
}

void BulletManager::BulletTracer::Configure(void)
{
	m_pkGeometry = new vrGeometry();
	m_pkGeometry->setPrimitive(vrGeometry::PRIMITIVE_POINT);

    vuVec4<float> *color = vuAllocArray<vuVec4<float> >::malloc(1);
    color[0].set(1.0f, 1.0f, 1.0f, 1.0f);
    m_pkGeometry->setColors(color, vrGeometry::BINDING_OVERALL);

    vuVec3<float> *pvfVertex = vuAllocArray<vuVec3<float>>::malloc(1);
    m_pkGeometry->setVertices(pvfVertex);

    m_pkRenderStrategy = new vsRenderStrategyFrameGeometry(m_pkGeometry, 
								vsRenderStrategyFrameGeometry::ATTRIBUTE_VERTICES);
    m_pkRenderStrategy->ref();
    m_pkGeometry->setRenderStrategy(m_pkRenderStrategy);
    m_pkGeometry->ref();

	// create our tracer state.  Probably easiest to just start w/ a basic
    // state here since we don't want the tracers to be lit, textured, etc.
    // However, we'll add a point element to increase the size of the
    // points and make them easier to see.
    vrState *pkState = new vrState(true);
    vrPoint::Element kPointElement;
    kPointElement.m_enableAntiAlias = true;
    kPointElement.m_size = 2.0f;
    pkState->setElement(vrPoint::Element::Id, &kPointElement);

    // create a geometry node and add our tracers to the scene
    m_pkBulletNode = new vsGeometry();
    m_pkBulletNode->setGeometry(m_pkGeometry);
    m_pkBulletNode->setState(pkState);
    m_pkBulletNode->ref();

	m_pkRecord = new BulletRecord();
	m_isector = new vpIsectorLOS();
	m_isector->setTarget(*vpScene::begin());
	m_isector->setIsectMask(ISECTOR_MASK);
	m_isector->ref();

	if (BulletManager::GetDrawTracers())
	{
		vpScene *scene = *vpScene::begin();
		scene->push_back_child(m_pkBulletNode);
	}
}

void BulletManager::BulletTracer::Fire(const vuVec3<double>& pvdEntryPoint)
{
	(*vpObserver::begin())->getTranslate(&m_vdPosition[0], &m_vdPosition[1], &m_vdPosition[2]);
	
	vuMatrix<double> rmat;
    rmat.makeRotate(pvdEntryPoint[0], pvdEntryPoint[1], pvdEntryPoint[2]);

	m_vdVelocity = INITIAL_TRACER_VELOCITY;
	rmat.transformPoint(&m_vdVelocity);
}

void BulletManager::Fire(const vuVec3<double>& pvdEntryPoint)
{
	ASSERT(m_lpkAvailableBullets.size())

	BulletTracer* pkTracer = m_lpkAvailableBullets.back();
	pkTracer->Fire(pvdEntryPoint);
	m_lpkAvailableBullets.pop_back();

	if (! m_lpkAvailableBullets.size())
	{
		for (int i = 0; i < m_lpkActiveBullets.size(); ++i)
		{
			m_lpkAvailableBullets.push_back(new BulletTracer());
		}
	}
}

int BulletManager::Configure(void)
{
	for (int i = 0; i < STARTING_TRACERS; ++i)
	{
		m_lpkAvailableBullets.push_back(new BulletTracer());
	}

	return vsgu::SUCCESS;
}

void BulletManager::Update(void)
{
    double dTime = vpKernel::instance()->getSimulationDeltaTime();

	vuList<BulletTracer*>::iterator& kIter = m_lpkActiveBullets.begin();

	while (kIter != m_lpkActiveBullets.end())
	{
		if ((*kIter)->Update(dTime))
		{
			m_lpkAvailableBullets.push_back(*kIter);
			kIter = m_lpkAvailableBullets.erase(kIter);
		}
		else
		{
			++kIter;
		}
	}
}



