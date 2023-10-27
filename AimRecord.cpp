#include <AimRecord.h>
#include <stdio.h>

void AimRecord::Serialize(FILE* pkLogFile)
{
	fprintf_s(pkLogFile, "%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", m_iWeaponType, m_dReceiveTime, m_dAimTime,
														   m_vdAimPix[0], m_vdAimPix[1],
														   m_vdStartPos[0], m_vdStartPos[1], m_vdStartPos[2],
														   m_vdEndPos[0], m_vdEndPos[1], m_vdEndPos[2]
	);

	
}

void AimRecord::Deserialize(FILE* pkLogFile)
{
	fscanf_s(pkLogFile, "%d%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf", &m_iWeaponType, &m_dReceiveTime, &m_dAimTime,
														   &(m_vdMousePos[0]), &(m_vdMousePos[1]),
														   &(m_vdStartPos[0]), &(m_vdStartPos[1]), &(m_vdStartPos[2]),
														   &(m_vdEndPos[0]), &(m_vdEndPos[1]), &(m_vdEndPos[2]));
}