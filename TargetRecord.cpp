#include <TargetRecord.h>
#include <IHitRegion.h>
#include <stdio.h>

TargetRecord::TargetRecord(void)
{

}

TargetRecord::~TargetRecord(void)
{

}

// SMB 17 Aug 2023: This was the new Serialize - Cmpatible format to current Weapon Manager app

void TargetRecord::Serialize(FILE* pkLogFile)
{
	fprintf(pkLogFile, "%lf %lf %lf %lf %lf", 
		m_vdPosition[0], m_vdPosition[1], m_vdPosition[2],
		m_vdCOMScreenCoordinates[0], m_vdCOMScreenCoordinates[1] );
}

// SMB 17 Aug 2023: This was the old Serialize - incompatible format to current Weapon Manager app
/*
void TargetRecord::Serialize(FILE* pkLogFile)
{
// SMB 26 Jul 2023 WAS: 	fprintf(pkLogFile, "%lf%lf%lf%lf%lf%lf%lf%%lf%lf%lf%lf%lf%d%d", GetTime(), 
//			removed apparently extranouse "%"
	fprintf(pkLogFile, "%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%d%llu", GetTime(), 
												  m_vdPosition[0], m_vdPosition[1], m_vdPosition[2], 
												  m_vdRotation[0], m_vdRotation[1], m_vdRotation[2], 
												  m_vdCenterOfMass[0], m_vdCenterOfMass[1], m_vdCenterOfMass[2],
												  m_vdCOMScreenCoordinates[0], m_vdCOMScreenCoordinates[1],
												  GetState(), m_lkHitRegionStates.size());
	
	vuList<IHitRegion::RegionState>::const_iterator kIter = m_lkHitRegionStates.begin();

	for (kIter; kIter != m_lkHitRegionStates.end(); ++kIter)
	{
		fprintf(pkLogFile, "%d", *kIter);
	}
}
*/

void TargetRecord::Deserialize(FILE* pkLogFile)
{
	int iRegionCount;

	// SMB 26 Jul 2023 WAS: 	fscanf_s(pkLogFile, "%lf%lf%lf%lf%lf%lf%lf%%lf%lf%lf%lf%lf%d%d", &m_dTime, 
	//			removed apparently extranouse "%"
	fscanf_s(pkLogFile, "%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%d%d", &m_dTime,
												   &(m_vdPosition[0]), &(m_vdPosition[1]), &(m_vdPosition[2]),
												   &(m_vdRotation[0]), &(m_vdRotation[1]), &(m_vdRotation[2]), 
												   &(m_vdCenterOfMass[0]), &(m_vdCenterOfMass[1]), &(m_vdCenterOfMass[2]),
												   &(m_vdCOMScreenCoordinates[0]), &(m_vdCOMScreenCoordinates[1]),
												   &m_kState, &iRegionCount);
	for (int i = 0; i < iRegionCount; ++i)
	{
		int iRegionState;
		fscanf_s(pkLogFile, "%d", &iRegionState);
		m_lkHitRegionStates.push_back((IHitRegion::RegionState) iRegionState);
	}
}