#include <GunManager.h>
#include <SingleShotFiringMode.h>
#include <BurstFiringMode.h>
#include <AutoFiringMode.h>
#include <vpChannel.h>
#include <vpInputMouse.h>
#include <vpObserver.h>
#include <vpMarineOcean.h>


GunManager* GunManager::s_pkInstance = NULL;

GunManager::GunManager(void) : m_kFireType(UNSET), m_pkFiringMode(NULL)
{
	
}

GunManager::~GunManager(void)
{
	if (m_pkFiringMode)
	{
		delete m_pkFiringMode;
	}
}

void GunManager::Configure(void)
{
	if (m_pkFiringMode)
	{
		delete m_pkFiringMode;
		m_pkFiringMode = NULL;
	}
	
	switch(m_kFireType)
	{
		case SINGLE_SHOT:
		{
			m_pkFiringMode = new SingleShotFiringMode();
			break;
		}
		case BURST:
		{
			m_pkFiringMode = new BurstFiringMode();
			break;
		}
		case AUTO:
		{
			m_pkFiringMode = new AutoFiringMode();
			break;
		}
		default:
		{
			break;
		}
	}
}

void GunManager::Fire(void)
{
	m_pkFiringMode->Fire();
}

void GunManager::Update(double dDeltaTime)
{
	m_pkFiringMode->Update(dDeltaTime);

	m_vdMotionPlatformAdjustmentPoint[2] = (*vpMarineOcean::begin())->getDepth(m_vdMotionPlatformAdjustmentPoint[0],
																			   m_vdMotionPlatformAdjustmentPoint[1]);
}

void GunManager::TriggerReleased(void)
{
	m_pkFiringMode->TriggerReleased();
}

void GunManager::GetMouseHeadingPitch(double* dHeading, double* dPitch, vuVec3<double>* pvdDirVec)
{
	
	vpInputMouse* pkMouse = *vpInputMouse::begin();

	float fMX = pkMouse->getSourceFloat(vpInputMouse::SOURCE_FLOAT_POSITION_X)->getValue();
	float fMY = pkMouse->getSourceFloat(vpInputMouse::SOURCE_FLOAT_POSITION_Y)->getValue();

	GetHeadingPitchFromMouseCoordinates(dHeading, dPitch, fMX, fMY, pvdDirVec);
}

void GunManager::GetMousePixelCoordinates(float* fMX, float* fMY)	
{
	vpInputMouse* pkMouse = *vpInputMouse::begin();

	*fMX = (float) pkMouse->getSourceInteger(vpInputMouse::SOURCE_INTEGER_POSITION_X)->getValue();
	*fMY = (float) pkMouse->getSourceInteger(vpInputMouse::SOURCE_INTEGER_POSITION_Y)->getValue();
}

void GunManager::GetHeadingPitchFromMouseCoordinates(double* dHeading, double* dPitch, float fMX, float fMY,
																	vuVec3<double>* pvdDirVec)
{
	vuMatrix<float> matfProjInv;
	vuVec3<float> vfMousePos = vuVec3<float>(fMX, fMY, -1);

	vpChannel* pkChannel = *vpChannel::begin();

	matfProjInv.invert(pkChannel->getVrChannel()->getProjectionMatrix());
	matfProjInv.transformPoint(&vfMousePos);
	pkChannel->getVrChannel()->getOffsetMatrixInverse().transformPoint(&vfMousePos);
	pkChannel->getVrChannel()->getViewMatrix().transformPoint(&vfMousePos);

	const vuMatrix<double> &viewMat = pkChannel->getViewMatrix();

	vuVec3<double> vec;

    vec[0] = vfMousePos[0] - viewMat[3][0];
    vec[1] = vfMousePos[1] - viewMat[3][1];
    vec[2] = vfMousePos[2] - viewMat[3][2];

	*pvdDirVec = vec;
	pvdDirVec->normalize();

	*dHeading = vuRad2Deg(vuArcTan(-vec[0], vec[1]));
	*dPitch = vuRad2Deg(vuArcTan(vec[2], vuSqrt(vuSq(vec[0]) + vuSq(vec[1]))));
}

void GunManager::SetLagAdjustmentPoint(void)
{
	vpObserver* pkObserver = *vpObserver::begin();
	const float fWaveDir = (*vpMarineOcean::begin())->getDominantWaveDirection();

	double dPosX, dPosY, dPosZ, dRotX, dRotY, dRotZ;
	
	pkObserver->getTranslate(&dPosX, &dPosY, &dPosZ);
	pkObserver->getRotate(&dRotX, &dRotY, &dRotZ);
}

void GunManager::Reset(void)
{
	m_pkFiringMode->TriggerReleased();
}

void GunManager::Start(void)
{

}