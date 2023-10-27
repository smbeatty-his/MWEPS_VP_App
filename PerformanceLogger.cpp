#include <PerformanceLogger.h>
#include <BulletManager.h>
#include <AimRecord.h>
#include <AimManager.h>
#include <TargetManager.h>
#include <TargetRecord.h>


PerformanceLogger* PerformanceLogger::s_pkInstance = NULL;

PerformanceLogger::PerformanceLogger(void)
{

}

PerformanceLogger::~PerformanceLogger(void)
{

}

// SMB 16 Aug 2023 - this is the new data file format and data

void PerformanceLogger::LogPerformanceData(const char* sFilename)
{
	FILE* pkLogFile;
	fopen_s(&pkLogFile, sFilename, "wb");

	m_kHeader.iAimRecords = AimManager::GetInstance()->GetAimRecords().size();
	m_kHeader.iShotRecords = BulletManager::GetInstance()->GetBulletRecords().size();
	m_kHeader.iTargetRecords = TargetManager::GetInstance()->GetNumTargetInstances();
	
	fprintf(pkLogFile, "WeaponType  ReceiveTime EventTime AimXPix AimYPix AimVecStartX AimVecStartY AimVecStartZ AimVecEndX AimVecEndY AimVecEndZ HitObject TargCMX TargCMY TargCMZ TargCMXPix TargCMYPix\n");

	// SMB: Currently, there is only one Target  -------------

	vuList<ITarget*>::const_iterator kTargetIter = TargetManager::GetInstance()->GetTargetInstanceList().begin();
	ITarget* pkTarget = *kTargetIter;

	vuVec3d TargetCM = pkTarget->GetCenterOfMass(); // Get X, Y, Z coordinates
	const char* TargetName = pkTarget->GetName();
	
	//SMB 20 Aug 2023: Get "Pixel" X, Y coordinates - these don't look like pixel coordinates
	//		but they match the old data files. Converts CenterOfMass coordinates into [0.0 to 1.0] screen coordinates
	vuVec2d TargetCMPix;
	TargetCMPix = pkTarget->GetCOMScreenCoordinates(TargetCM);

	vuList<AimRecord*>::const_iterator kAimIter = AimManager::GetInstance()->GetAimRecords().begin();
	vuList<AimRecord*>::const_iterator kAimEndIter = AimManager::GetInstance()->GetAimRecords().end(); 

	for (kAimIter; kAimIter != kAimEndIter; ++kAimIter)
	{
		(*kAimIter)->Serialize(pkLogFile);
		fprintf(pkLogFile, " %s", TargetName); 

		// Repeat same single target info after each Aim Record
		fprintf(pkLogFile, " %lf %lf %lf %lf %lf", TargetCM[0], TargetCM[1], TargetCM[2], 
			TargetCMPix[0], TargetCMPix[1]);  //SMB WAS Target Record: m_vdCOMScreenCoordinates[0], m_vdCOMScreenCoordinates[1]);
		
		fprintf(pkLogFile, "\n");
	}

	fclose(pkLogFile);
}

// SMB 16 Aug 2023: This was the old file generator - incompatible format and data for current Weapon Manager application
/*
void PerformanceLogger::LogPerformanceData(const char* sFilename)
{
	FILE* pkLogFile;
	fopen_s(&pkLogFile, sFilename, "wb");

	m_kHeader.iAimRecords = AimManager::GetInstance()->GetAimRecords().size();
	m_kHeader.iShotRecords = BulletManager::GetInstance()->GetBulletRecords().size();
	m_kHeader.iTargetRecords = TargetManager::GetInstance()->GetNumTargetInstances();

	fprintf(pkLogFile, "%d%d%d", m_kHeader.iAimRecords, m_kHeader.iShotRecords, m_kHeader.iTargetRecords);

	vuList<AimRecord*>::const_iterator kAimIter = AimManager::GetInstance()->GetAimRecords().begin();
	vuList<AimRecord*>::const_iterator kAimEndIter = AimManager::GetInstance()->GetAimRecords().end();

	for (kAimIter; kAimIter != kAimEndIter; ++kAimIter)
	{
		(*kAimIter)->Serialize(pkLogFile);
	}

	vuList<BulletRecord*>::const_iterator kBulletIter = BulletManager::GetInstance()->GetBulletRecords().begin();
	vuList<BulletRecord*>::const_iterator kBulletEndIter = BulletManager::GetInstance()->GetBulletRecords().end();

	for (kBulletIter; kBulletIter != kBulletEndIter; ++kBulletIter)
	{
		(*kBulletIter)->Serialize(pkLogFile);
	}

	vuList<ITarget*>::const_iterator kTargetIter = TargetManager::GetInstance()->GetTargetInstanceList().begin();
	vuList<ITarget*>::const_iterator kTargetEndIter = TargetManager::GetInstance()->GetTargetInstanceList().end();

	for (kTargetIter; kTargetIter != kTargetEndIter; ++kTargetIter)
	{
		ITarget* pkTarget = *kTargetIter;
		fprintf(pkLogFile, "%llu %s %llu", sizeof(pkTarget->GetName()) + 1, pkTarget->GetName(), pkTarget->GetTargetRecords().size());
		vuList<TargetRecord*>::const_iterator kTargetRecIter = pkTarget->GetTargetRecords().begin();
		vuList<TargetRecord*>::const_iterator kTargetRecEndIter = pkTarget->GetTargetRecords().end();

		for (kTargetRecIter; kTargetRecIter != kTargetRecEndIter; ++kTargetRecIter)
		{
			(*kTargetRecIter)->Serialize(pkLogFile);
		}
	}

	fclose(pkLogFile);
}
*/

void PerformanceLogger::LoadPerformanceData(const char* sFilename)
{
	FILE* pkLogFile;
	fopen_s(&pkLogFile, sFilename, "rb");

	int iAimRecords;
	int iShotRecords;
	int iTargetRecords;

	fscanf(pkLogFile, "%d%d%d", &iAimRecords, &iShotRecords, &iTargetRecords);

	AimManager::GetInstance()->ClearAimRecords();

	for (int i = 0; i < iAimRecords; ++i)
	{
		AimRecord* pkRecord = new AimRecord();
		pkRecord->Deserialize(pkLogFile);
		AimManager::GetInstance()->AddAimRecord(pkRecord);
	}

	BulletManager::GetInstance()->ClearBulletRecords();

	for (int i = 0; i < iShotRecords; ++i)
	{
		BulletRecord* pkRecord = new BulletRecord();
		pkRecord->Deserialize(pkLogFile);
		BulletManager::GetInstance()->AddExpiredBullet(pkRecord);
	}

	for (int i = 0; i < iTargetRecords; ++i)
	{
		int iTargetNameSize;
		fscanf_s(pkLogFile, "%d", &iTargetNameSize);

		char* sTargetName = new char[iTargetNameSize];
		fscanf_s(pkLogFile, "%s", sTargetName, iTargetNameSize);
		ITarget* pkTarget = TargetManager::GetInstance()->GetTargetInstanceByName(sTargetName);
		pkTarget->ClearTargetRecords();

		int iNumRecords;
		fscanf_s(pkLogFile, "%d", &iNumRecords);

		// SMB WAS: for (int i = 0; i < iNumRecords; ++i)  ... which overwrites index variable in enclosing loop!
		for (int j = 0; j < iNumRecords; ++j)
		{
			TargetRecord* pkRecord = new TargetRecord();
			pkRecord->Deserialize(pkLogFile);
			pkTarget->AddTargetRecord(pkRecord);
		}
	}

	fclose(pkLogFile);
}
