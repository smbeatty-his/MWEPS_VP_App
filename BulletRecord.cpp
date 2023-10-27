#include <BulletRecord.h>
#include <stdio.h>

void BulletRecord::Serialize(FILE *pkLogFile)
{
	int iNumPoints = m_lvdVisitedPoints.size();

	fprintf(pkLogFile, "%lf%d", m_dFiredTime, iNumPoints);
	
	vuList<vuVec3<double>>::const_iterator kIter = m_lvdVisitedPoints.begin();

	for (kIter; kIter != m_lvdVisitedPoints.end(); ++kIter)
	{
		fprintf(pkLogFile, "%lf%lf%lf", (*kIter)[0], (*kIter)[1], (*kIter)[2]);
	}

	int iNameSize = strlen(m_sHitObject) + 1;

	fprintf(pkLogFile, "%d%s", iNameSize, m_sHitObject);
}

void BulletRecord::Deserialize(FILE* pkLogFile)
{
	int iNumPoints;
	fscanf_s(pkLogFile, "%lf%d", &m_dFiredTime, &iNumPoints);

	for (int i = 0; i < iNumPoints; ++i)
	{
		vuVec3<double> vdPoint;
		fscanf_s(pkLogFile, "%lf%lf%lf", &(vdPoint[0]), &(vdPoint[1]), &(vdPoint[2]));
		m_lvdVisitedPoints.push_back(vdPoint);
	}

	int iNameSize;
	fscanf_s(pkLogFile, "%d", &iNameSize);
	fscanf_s(pkLogFile, "%s", m_sHitObject, iNameSize);
}