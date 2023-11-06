#include <AimManager.h>
#include <AimRecord.h>
#include <vuVec3.h>
#include <vpChannel.h>
#include <vpInputMouse.h>
#include <vpKernel.h>
#include <TPManager.h>
#include <vpOverlay2DImage.h>
#include <vpObject.h>
#include <GunManager.h>
#include <vpScene.h>


AimManager* AimManager::s_pkInstance = 0;

AimManager::AimManager(int iPulseRate) : m_pkCrosshair(NULL)
{
	m_iAimPulseRate = iPulseRate;
	m_dAimPulseDelay = 1.0 / iPulseRate;
	m_dAimDelayedTime = 0.0;
	// SMB: local variable never used
	// vpChannel* pkChannel = *vpChannel::begin();
	m_kIsector = new vpIsectorLOS();
	m_kIsector->ref();
	m_kIsector->setTarget(*vpScene::begin());
}

AimManager::~AimManager(void)
{
	Reset();

	m_kIsector->unref();
	m_pkMouse->unref();
}

// SMB: AimManager::Update Adds an IOS_WM_AIM event with the position of the mouse to the m_PkWMShare event queue
void AimManager::Update(double dDeltaTime)
{
	m_dAimDelayedTime += dDeltaTime;

	float fMX = m_pkMouse->getSourceFloat(vpInputMouse::SOURCE_FLOAT_POSITION_X)->getValue();
	float fMY = m_pkMouse->getSourceFloat(vpInputMouse::SOURCE_FLOAT_POSITION_Y)->getValue();

	WMEvent kCrosshairUpdate;

	kCrosshairUpdate.bEvent = true;
	kCrosshairUpdate.iEventType = IOS_WM_CROSSHAIR;
	kCrosshairUpdate.fData[0] = (fMX + 1.0f) / 2.0f;
	kCrosshairUpdate.fData[1] = (fMY + 1.0f) / 2.0f; 

	TPManager::GetInstance()->TestIncomingEvent(kCrosshairUpdate);  //SMB: puts KCrosshairUpdate event into 1st empty m_PkWMShare.Ev[i] slot

	if (m_dAimDelayedTime >= m_dAimPulseDelay)
	{
		WMEvent kAimUpdate;

		fMX = (float) m_pkMouse->getSourceInteger(vpInputMouse::SOURCE_INTEGER_POSITION_X)->getValue();
		fMY = (float) m_pkMouse->getSourceInteger(vpInputMouse::SOURCE_INTEGER_POSITION_Y)->getValue();

		kAimUpdate.bEvent = true;
		kAimUpdate.iEventType = IOS_WM_AIM;
		kAimUpdate.fData[0] = fMX;
		kAimUpdate.fData[1] = fMY;

		TPManager::GetInstance()->TestIncomingEvent(kAimUpdate);

		m_dAimDelayedTime = 0.0;
	}
}

void AimManager::Start(void)
{

}

void AimManager::Reset(void)
{
	while (m_lpkAimRecords.size())
	{
		AimRecord* pkRecord = m_lpkAimRecords.back();
		m_lpkAimRecords.pop_back();
		delete pkRecord;
	}
}

void AimManager::PushAim(const WMEvent& kEvent, const double dReceiveTime)
{
	// SMB 14 Aug 202 WAS: (for mouse position)
//	float fAimPixX = kEvent.fData[0];
//	float fAimPixY = kEvent.fData[1];

	// SMB 14 Aug 2023 For Spot Tracker position from BFFTrack
	float fAimPixX = kEvent.fData[1];
	float fAimScreenX = kEvent.fData[1];
	float fAimPixY = kEvent.fData[2];
	float fAimScreenY = kEvent.fData[2];


/*	
	// This moves the Crosshair across the screen - shows the visible limits of screen
	static float fMovingAimX = 0.0f;
	static float fMovingAimY = 0.0f;
	fMovingAimX += 0.01f;
	fMovingAimY += 0.01f;
	if (fMovingAimX >= 1.0f) {
		fMovingAimX = 0.0f;
		fMovingAimY = 0.0f;
	}
*/
	GetScreenCoordinates(&fAimScreenX, &fAimScreenY);  //SMB: Converts to Screen Coordinates -1.0 to 1.0


	// SMB 14 Aug 2023: Move our Crosshair accordingly
	// SMB 14 Aug 2023: Convert to 0.0 to 1.0 for Crosshair origin and add Crosshair adjustments
//	m_pkAimCrosshair->setOrigin( ((fAimScreenX + 1.0f) / 2.0f) - m_vfCrosshairAdjustment[0],
//		((fAimScreenY + 1.0f) / 2.0f) - m_vfCrosshairAdjustment[1]); // 0.0 to 1.0
	m_pkAimCrosshair->setEnable(TRUE); //It's turned off by default in the ACF file, so we can lock onto the target
	m_pkAimCrosshair->setOrigin(((fAimScreenX + 1.0f) / 2.0f) - 0.0018 ,
		((fAimScreenY + 1.0f) / 2.0f) + 0.038); // 0.0 to 1.0


	double dHeading, dPitch;
	vuVec3<double> vdAimDirection;

	vpChannel* pkChannel = *vpChannel::begin();

	//SMB: Removed ... we're using Laser Spot, not mouse
	// GunManager::GetInstance()->GetHeadingPitchFromMouseCoordinates(&dHeading, &dPitch, fAimPixX, fAimPixY, &vdAimDirection);

	float fNearPlane, fFarPlane;

	pkChannel->getNearFar(&fNearPlane, &fFarPlane);

	const vuMatrix<double> &viewMat = pkChannel->getViewMatrix();

	vdAimDirection *= 2.0 * (double)fFarPlane;

	m_kIsector->setTranslate(viewMat[3][0], viewMat[3][1], viewMat[3][2]);
	m_kIsector->setRotate(dHeading, dPitch, 0.0);
	m_kIsector->setSegmentRange(2 * (double)fFarPlane);

	m_kIsector->update();

	//if (m_kIsector->getHit())
	//{
	//	if (m_kIsector->getHitObject())
	//	{
	//		printf("Hit Object: %s\n", m_kIsector->getHitObject()->getName());
	//	}

	//	else if (m_kIsector->getHitNode())
	//	{
	//		printf("Hit Node: %s\n", m_kIsector->getHitNode()->getName());
	//	}

	//	vuVec3<double> vdHitPoint;

	//	m_kIsector->getHitPoint(&vdHitPoint);

	//	printf("Hit Point: %f, %f, %f\n", vdHitPoint[0], vdHitPoint[1], vdHitPoint[2]);
	//}

	//else
	//{
	//	printf("No Hit!\n");
	//}

	AimRecord* pkAimRecord = new AimRecord();
	pkAimRecord->SetAimTime(vpKernel::instance()->getSimulationTime());

	vuVec3<double> vdStartPos = vuVec3<double>(viewMat[3][0], viewMat[3][1], viewMat[3][2]);
	vuVec3<double> vdEndPos = vuVec3<double>(vdAimDirection[0], vdAimDirection[1], vdAimDirection[2]);

	//SMB 16 Aug 2023: Add Aim Pixel X, Y to Aim Record
	vuVec2<double> vdAimPix = vuVec2<double>(fAimPixX, fAimPixY);
	pkAimRecord->SetAimPix(vdAimPix);

	pkAimRecord->SetStartPos(vdStartPos);
	pkAimRecord->SetEndPos(vdEndPos);

	m_lpkAimRecords.push_back(pkAimRecord);

}

void AimManager::GetScreenCoordinates(float *fX, float *fY)
{
	*fX = -1.0f * (SCREEN_WIDTH_CENTER - *fX) / SCREEN_WIDTH_CENTER;
    *fY = -1.0f * (SCREEN_HEIGHT_CENTER - *fY) / SCREEN_HEIGHT_CENTER;
}

// Sets the information we parsed into our new pkCrosshair into the member variable
void AimManager::SetCrosshair()
{
	// SMB: This Crosshair is defined in the .acf file
	m_pkAimCrosshair = vpOverlay2DImage::find("AimCrosshair");
	
	float fScaleX, fScaleY;
	m_pkAimCrosshair->getScale(&fScaleX, &fScaleY);
	m_vfCrosshairAdjustment.set(fScaleX / 2.0f, fScaleY / 2.0f);
}

// SMB 06Nov2023 - We don't call this anymore. Crosshair responds to Laser spot
//				   That's handled with PushAim and event IOS_WM_AIM
//				   m_pkCrosshair is not longer used
/*
void AimManager::UpdateCrosshairPosition(const WMEvent &kEvent)
{
	ASSERT(m_pkCrosshair)

	//SMB 10 Aug 2023: m_pkCrosshair WILL NOT BE DISPLAYED ... don't know why
		m_pkCrosshair->setOrigin(kEvent.fData[0] - m_vfCrosshairAdjustment[0],
								kEvent.fData[1] - m_vfCrosshairAdjustment[1]);
}
*/

void AimManager::ClearAimRecords(void)
{
	while (m_lpkAimRecords.size())
	{
		AimRecord* pkRecord = m_lpkAimRecords.back();
		m_lpkAimRecords.pop_back();
		delete pkRecord;
	}
}
