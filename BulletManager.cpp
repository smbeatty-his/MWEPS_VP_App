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
#include <vpObserver.h>
#include <BulletManager.h>
#include <ParticleSystemManager.h>
#include <SoundManager.h>
#include <BulletRecord.h>
#include <DebugUtil.h>
#include <TargetManager.h>
#include <ITarget.h>
#include <TPManager.h>
#include <AimManager.h>
#include <GunManager.h>

#define INITIAL_TRACER_VELOCITY vuVec3<double> (0.0, 1000.0, 0.0);
#define ISECTOR_MASK 0xFFFFFFFF
#define WATER_OBJECT "OceanObserverCentered"
#define SPLASH_OBJECT "Splash"
#define WATER_EFFECT_END_TIME 5.0f
#define TEST_BORE_LENGTH 1.0f

BulletManager* BulletManager::s_pkInstance = 0;

///////////////////////////////////////////////////////////////////////////////
///
///	BulletManager::BulletManager
///	
///	@brief Constructor
///
///////////////////////////////////////////////////////////////////////////////

BulletManager::BulletManager() : m_iRoundsFired(0), m_iGroupRoundsFired(0)
{ 
	m_bDrawTracers = true;
	Configure();
}

///////////////////////////////////////////////////////////////////////////////
///
///	BulletManager::~BulletManager
///	
///	@brief Destructor
///
///////////////////////////////////////////////////////////////////////////////
BulletManager::~BulletManager(void)
{
	m_pkGeometry->setRenderStrategy(NULL);
    m_pkRenderStrategy->unref();
    m_pkGeometry->unref();
    m_pkBulletNode->unref();

	Reset();

	while (m_lpkAvailableBullets.size())
	{
		BulletTracer* pkTracer = m_lpkAvailableBullets.back();
		m_lpkAvailableBullets.pop_back();
		delete pkTracer;
	}
}

///////////////////////////////////////////////////////////////////////////////
///
///	BulletManager::Shutdown
///	
///	@brief Used to clean up singleton instance
///
///////////////////////////////////////////////////////////////////////////////

void BulletManager::Shutdown(void)
{
	delete s_pkInstance;
}

///////////////////////////////////////////////////////////////////////////////
///
///	BulletManager::Configure
///	
///	@brief Configures singleton instance of BulletManager for use
///
///////////////////////////////////////////////////////////////////////////////

int BulletManager::Configure(void)
{
        // create our tracer geometry.  Here we'll just use simple point
        // primitives, all of which are the same color, and we'll use a render
        // strategy so it's safe to update our geometry in a multi-threaded
        // environment.  Note here that since there are no tracers active at
        // the start of the application so we won't actually set the number of
        // primitives to start with.
        m_pkGeometry = new vrGeometry();
        m_pkGeometry->setPrimitive(vrGeometry::PRIMITIVE_POINT);
        vuVec4<float> *color = vuAllocArray<vuVec4<float> >::malloc(1);
        color[0].set(1.0f, 1.0f, 1.0f, 1.0f);
        m_pkGeometry->setColors(color, vrGeometry::BINDING_OVERALL);
        vuVec3<float> *vertex = vuAllocArray<vuVec3<float>>::malloc(MAX_NUM_TRACERS);
        m_pkGeometry->setVertices(vertex);
        m_pkRenderStrategy = new vsRenderStrategyFrameGeometry(
            m_pkGeometry, vsRenderStrategyFrameGeometry::ATTRIBUTE_VERTICES);
        m_pkRenderStrategy->ref();
        m_pkGeometry->setRenderStrategy(m_pkRenderStrategy);
        m_pkGeometry->ref();

		for (int i = 0; i < MAX_NUM_TRACERS; ++i)
		{
			m_apTracer[i].m_bActive = false;
			m_apTracer[i].m_isector = NULL;
			m_apTracer[i].m_pkRecord = new BulletRecord();
		}

        // create our tracer state.  Probably easiest to just start w/ a basic
        // state here since we don't want the tracers to be lit, textured, etc.
        // However, we'll add a point element to increase the size of the
        // points and make them easier to see.
        vrState *state = new vrState(true);
        vrPoint::Element pointElement;
        pointElement.m_enableAntiAlias = true;
        pointElement.m_size = 2.0f;
        state->setElement(vrPoint::Element::Id, &pointElement);

        // create a geometry node and add our tracers to the scene
        m_pkBulletNode = new vsGeometry();
        m_pkBulletNode->setGeometry(m_pkGeometry);
        m_pkBulletNode->setState(state);
        m_pkBulletNode->ref();

		if (m_bDrawTracers)
		{
			(*vpScene::begin())->push_back_child(m_pkBulletNode);
		}

		m_iInactiveIndex = 0;

        return vsgu::SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
///
///	BulletManager::Update
///	
///	@brief Handles updates of bullets in scene, check for impacts and removing
///		   them should they occur
///
///////////////////////////////////////////////////////////////////////////////

void BulletManager::Update(double dTime)
{
    int numPrimitives = 0;
    const double dGravity = -9.8;
    vuVec3<float>* pvfVertex = m_pkGeometry->getVertices();

    for (int i = 0; i < MAX_NUM_TRACERS; ++i) 
	{
        if (m_apTracer[i].m_bActive) 
		{
			m_apTracer[i].m_pkRecord->AddPoint(&m_apTracer[i].m_vdPosition);
            // compute the new velocity vector
			m_apTracer[i].UpdateVelocity(dTime);

			m_apTracer[i].m_isector->setPosition(m_apTracer[i].m_vdPosition[0], 
												 m_apTracer[i].m_vdPosition[1],
												 m_apTracer[i].m_vdPosition[2]);

            // compute the new position
			
			m_apTracer[i].m_vdPosition = m_apTracer[i].m_vdVelocity;

			//printf("Tracer located at position %f, %f, %f\n", m_apTracer[i].m_vdPosition[0], 
											//m_apTracer[i].m_vdPosition[1], m_apTracer[i].m_vdPosition[2]);

			
			
			vuVec3<double> vdDistTraveled;
			m_apTracer[i].m_isector->getPosition(&(vdDistTraveled[0]), &(vdDistTraveled[1]), &(vdDistTraveled[2]));

			vdDistTraveled[0] = m_apTracer[i].m_vdPosition[0] - vdDistTraveled[0];
			vdDistTraveled[1] = m_apTracer[i].m_vdPosition[1] - vdDistTraveled[1];
			vdDistTraveled[2] = m_apTracer[i].m_vdPosition[2] - vdDistTraveled[2];

			double dHeading = vuRad2Deg(-vuArcTan(vdDistTraveled[0], vdDistTraveled[1]));
			double dPitch = vuRad2Deg(vuArcTan(vdDistTraveled[2], 
								vuSqrt(vuSq(vdDistTraveled[0]) + vuSq(vdDistTraveled[1]))));

			m_apTracer[i].m_isector->setRotate(dHeading, dPitch, 0.0);
			m_apTracer[i].m_isector->setSegmentRange(vdDistTraveled.length());

			m_apTracer[i].m_isector->update();

			//if tracer hit something
			if (m_apTracer[i].m_isector->getHit())
			{
				m_apTracer[i].m_bActive = false;
				vpObject* pkObject = m_apTracer[i].m_isector->getHitObject();

				//was it an object
				if (pkObject)
				{
					printf("Hit Object %s\n", pkObject->getName());
					ASSERT(pkObject)
					//PrintAllChildren(pkObject);
					vsNode* pkNode = m_apTracer[i].m_isector->getHitNode();
					ASSERT(pkNode)
					printf("Hit Node %s\n", (*pkNode->begin_parent())->getName());
					//PrintAllParents(pkNode);
					ASSERT((*pkNode->begin_parent())->getName())
					
					// SMB: is the following pointer truncation to int correct?
					ITarget* pkTarget = TargetManager::GetInstance()->GetActiveTarget((unsigned int) pkObject);
					const char* sRegionName = (*pkNode->begin_parent())->getName();
					ASSERT(sRegionName)

					if (! pkTarget->GetRegionMap().count(sRegionName))
					{
						pvfVertex[numPrimitives++].set(m_apTracer[i].m_vdPosition[0],
													   m_apTracer[i].m_vdPosition[1],
                                                       m_apTracer[i].m_vdPosition[2]);
						return;
					}
					
					vuVec3<double> vdHitPos;
					m_apTracer[i].m_isector->getHitPoint(&vdHitPos);

					ShotPath* pkPath = m_apTracer[i].m_pkPath;

					m_apTracer[i].m_pkPath = NULL;

					delete pkPath;

					pkTarget->ProcessHit((*pkNode->begin_parent())->getName(), vdHitPos);

					//printf("\nHit Position: %lf, %lf, %lf\n", vdHitPos[0], vdHitPos[1], vdHitPos[2]);
					
					vuVec3<double> vdObjPos;
					pkObject->getTranslate(&vdObjPos[0], &vdObjPos[1], &vdObjPos[2]);
					//printf("Hit Object Position: %lf, %lf, %lf\n", vdObjPos[0], vdObjPos[1], vdObjPos[2]);

					vdHitPos[0] -= vdObjPos[0];
					vdHitPos[1] -= vdObjPos[1];
					vdHitPos[2] -= vdObjPos[2];

					//printf("Hit Offset: %lf, %lf, %lf\n", vdHitPos[0], vdHitPos[1], vdHitPos[2]);

				}

				//if not an object, currently it is assumed it is the ocean
				else
				{
					vsNode* pkNode = m_apTracer[i].m_isector->getHitNode();
					if (pkNode)
					{
						printf("Hit Node %s\n", pkNode->getName());
						if (pkNode->getName())
						{
							char* sName = "Splash"; 

							m_apTracer[i].m_isector->getHitPoint(&m_apTracer[i].m_vdPosition);

							SoundManager::GetInstance()->PlayEnviromentalSound(sName, m_apTracer[i].m_vdPosition);

							ParticleSystemManager::GetInstance()->AddParticleSystem(sName, m_apTracer[i].m_vdPosition);
						}
					}
				}
				
				m_apTracer[i].m_pkRecord->AddPoint(&m_apTracer[i].m_vdPosition);
				AddExpiredBullet(m_apTracer[i].m_pkRecord);
				//printf("Stored records: %d\n", m_lpkExpiredBullets.size());
				m_apTracer[i].m_pkRecord->Reset();
				

				if (i < m_iInactiveIndex)
				{
					m_iInactiveIndex = i;
				}
			}

            // otherwise, update the vertex data
            else 
			{
                pvfVertex[numPrimitives++].set(m_apTracer[i].m_vdPosition[0],
											   m_apTracer[i].m_vdPosition[1],
                                               m_apTracer[i].m_vdPosition[2]);
            }
        }
	}

	if (numPrimitives)
	{	
		m_pkGeometry->setNumPrimitives(numPrimitives);
	}

	m_pkGeometry->setVertices(pvfVertex);
	m_pkRenderStrategy->update();
	
	// update our bounding sphere
    m_pkBulletNode->dirtyUp(vsNode::DIRTY_BOUNDS);

	// don't render if we don't have any primitives
	if (numPrimitives > 0)
	{
		m_pkBulletNode->setRenderMask(0xffffffff);
	}
	else
	{
		m_pkBulletNode->setRenderMask(0x0);
	}
}

///////////////////////////////////////////////////////////////////////////////
///
///	BulletManager::Fire
///	
///	@brief Places bullet into scene at the desired point based on input of 
///		   mouse coordinates or data from weapon tracker.
///	@param pvdEntryPoint Point in World Space where bullet should enter scene
///
///////////////////////////////////////////////////////////////////////////////
void BulletManager::Fire(const vuVec3<double>& pvdEntryPoint)
{
	(*vpObserver::begin())->getTranslate(&(m_apTracer[m_iInactiveIndex].m_vdPosition[0]),
										 &(m_apTracer[m_iInactiveIndex].m_vdPosition[1]),
										 &(m_apTracer[m_iInactiveIndex].m_vdPosition[2]));

	BulletTracer* pkTracer = GetNextTracer();
	
	vuMatrix<double> rmat;
    rmat.makeRotate(pvdEntryPoint[0], pvdEntryPoint[1], pvdEntryPoint[2]);
	pkTracer->m_vdVelocity = INITIAL_TRACER_VELOCITY;
	rmat.transformPoint(&(pkTracer->m_vdVelocity));
	pkTracer->m_bTest = true;

	SoundManager::GetInstance()->PlayAmbientSound("Gunshot");
}

void BulletManager::Fire(void)
{
	SoundManager::GetInstance()->PlayAmbientSound("Gunshot");

	WMEvent kEvent;

	double dElapsedTime = vpKernel::instance()->getSimulationDeltaTime();

	kEvent.fData[0] = (float) dElapsedTime;

	GunManager::GetInstance()->GetMousePixelCoordinates(&(kEvent.fData[1]), &(kEvent.fData[2]));

	kEvent.fData[3] = 0.01666666f;
	kEvent.fData[4] = 1.0f;

	GenerateBulletPath(&kEvent);

	kEvent.iEventType = IOS_WM_SHOT;
	kEvent.bEvent = true;

	TPManager::GetInstance()->TestIncomingEvent(kEvent);
}

void BulletManager::PushBulletPath(const WMEvent& kEvent, const double dElapsedTime)
{
	float fEventTime = kEvent.fData[0];

	float fBoreLength = kEvent.fData[4];

	vuVec3<double> vdObserverPosition;
	(*vpObserver::begin())->getTranslate(&(vdObserverPosition[0]), &(vdObserverPosition[1]), &(vdObserverPosition[2]));

	float fAimPixX = kEvent.fData[1];
	float fAimPixY = kEvent.fData[2];

	double dH, dP;

	AimManager::GetInstance()->GetScreenCoordinates(&fAimPixX, &fAimPixY);

	vuVec3<double> vdTargetPoint;

	GunManager::GetInstance()->GetHeadingPitchFromMouseCoordinates(&dH, &dP, fAimPixX, fAimPixY, &vdTargetPoint);

	vdTargetPoint *= 2000.0;
	
	double dLength = vdTargetPoint.length();

	ShotPath* pkPath = new ShotPath();

	pkPath->m_iWeaponType = kEvent.iData[0];
	pkPath->m_iNumPoints = kEvent.iData[1];
	pkPath->m_dImpactTime = dElapsedTime;
	pkPath->m_dEventTime = fEventTime - 0.2;
	pkPath->m_dTimeInterval = kEvent.fData[3];
	pkPath->m_iPathIndex = 0;
	pkPath->m_dTotalTravelTime = 0.0;

	++m_iRoundsFired;

	for ( int i = 0; i < pkPath->m_iNumPoints; i++ )
    {
	    double xP = kEvent.balPath[i].x;
	    double yP = kEvent.balPath[i].y;
	    double zP = kEvent.balPath[i].z;
        // adjust path based on bore length
        yP += fBoreLength;
        double yPS = yP / dLength;
        vuVec3<double> vdPathPoint;
        // move point down vector based on bullet downrange position
        vdPathPoint.set(yPS * vdTargetPoint[0], yPS * vdTargetPoint[1], yPS * vdTargetPoint[2]);
        vdPathPoint[0] += xP;
		vdPathPoint[2] += zP;
        vdPathPoint += vdObserverPosition;
		pkPath->m_pnt[i] = vdPathPoint;
     }	
	
	BulletTracer* pkTracer = GetNextTracer();
	pkTracer->m_pkPath = pkPath;
	pkTracer->m_vdPosition = vdObserverPosition;

	pkTracer->m_bTest = false;
}

BulletManager::BulletTracer* BulletManager::GetNextTracer(void)
{
	m_apTracer[m_iInactiveIndex].m_bActive = true;

	if (m_apTracer[m_iInactiveIndex].m_isector == NULL)
	{
		m_apTracer[m_iInactiveIndex].m_isector = new vpIsectorLOS();
		m_apTracer[m_iInactiveIndex].m_isector->ref();
		m_apTracer[m_iInactiveIndex].m_isector->setTarget(*vpScene::begin());
		m_apTracer[m_iInactiveIndex].m_isector->setIsectMask(ISECTOR_MASK);
	}

	int iIndex = m_iInactiveIndex;

	for (int i = 0; i < MAX_NUM_TRACERS; ++i)
	{
		if (! m_apTracer[i].m_bActive)
		{
			m_iInactiveIndex = i;
			i = MAX_NUM_TRACERS;
		}
	}

	return &(m_apTracer[iIndex]);
}



void BulletManager::GenerateBulletPath(WMEvent* pkEvent)
{	
	float fPosX, fPosY, fPosZ;
	fPosX = fPosY = fPosZ = 0.0f;
	int i = 0;

	vuVec3<double> vdTracerPosition = vuVec3<double>(0.0, 2000.0, 0.0); 

	vuVec3<double> vdTracerVelocity = INITIAL_TRACER_VELOCITY;

	while (fPosY < vdTracerPosition[1] && i < 300)
	{
		fPosX += (float) (vdTracerVelocity[0] * pkEvent->fData[3]);
		fPosY += (float) (vdTracerVelocity[1] * pkEvent->fData[3]);
		fPosZ += (float) (vdTracerVelocity[2] * pkEvent->fData[3]);

		//printf("Creating path point at %f, %f, %f\n", fPosX, fPosY, fPosZ); 

		vdTracerVelocity[2] += -9.8 * pkEvent->fData[3];

		pkEvent->balPath[i].x = fPosX;
		pkEvent->balPath[i].y = fPosY;
		pkEvent->balPath[i].z = fPosZ;

		++i;
	}

	pkEvent->iData[1] = i;
}

void BulletManager::PrintAllChildren(vsNode* pkNode)
{
	
	vsNode::const_iterator_child kIter = pkNode->begin_child();

	for (kIter; kIter != pkNode->end_child(); ++kIter)
	{
		vsNode* pkChild = *kIter;
		printf("Child Node: %s\n", pkChild->getName());
		PrintAllChildren(pkChild);
	}
}

void BulletManager::PrintAllParents(vsNode* pkNode)
{
	
	vsNode::const_iterator_parent kIter = pkNode->begin_parent();

	for (kIter; kIter != pkNode->end_parent(); ++kIter)
	{
		vsNode* pkParent = *kIter;
		printf("Parent Node: %s\n", pkParent->getName());
		PrintAllParents(pkParent);
	}
}

void BulletManager::Reset(void)
{
	ClearBulletRecords();

	while (m_lpkShotPaths.size())
	{
		ShotPath* pkPath = m_lpkShotPaths.back();
		m_lpkShotPaths.pop_back();
		delete pkPath;
	}


	vuList<BulletTracer*>::iterator kIter = m_lpkActiveBullets.begin();

	for (kIter; kIter != m_lpkActiveBullets.end(); ++kIter)
	{	
		(*kIter)->m_pkRecord->Reset();
		(*kIter)->m_bActive = false;
		//m_lpkAvailableBullets.push_back(*kIter);
	}

	m_lpkActiveBullets.clear();

	m_iRoundsFired = 0;
	m_iGroupRoundsFired = 0;
}

void BulletManager::ClearBulletRecords(void)
{
	while (m_lpkExpiredBullets.size())
	{
		BulletRecord* pkRecord = m_lpkExpiredBullets.back();
		m_lpkExpiredBullets.pop_back();
		delete pkRecord;
	}
}	