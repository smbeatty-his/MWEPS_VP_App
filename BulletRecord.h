#ifndef BULLET_RECORD_MODULE_H
#define BULLET_RECORD_MODULE_H

#include <DebugUtil.h>
#include <vuList.h>
#include <vuVec3.h>

///////////////////////////////////////////////////////////////////////////////
///
/// @class BulletRecord
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class BulletRecord
{
public:

	BulletRecord() { }
	~BulletRecord() { }
	BulletRecord(const BulletRecord& kThat)
	{
		m_lvdVisitedPoints = kThat.m_lvdVisitedPoints;
		m_dFiredTime = kThat.m_dFiredTime;
		strcpy(m_sHitObject, kThat.m_sHitObject);
	};

	inline void AddPoint(vuVec3<double>* vdPoint) { m_lvdVisitedPoints.push_back(*vdPoint); }
	inline const vuList<vuVec3<double>> GetPointList(void) const { return m_lvdVisitedPoints; }
	inline void SetHitObject(char* sHitObject) { strcpy(m_sHitObject, sHitObject); }
	inline const char* GetHitObject(void) const { return m_sHitObject; }
	inline void Reset(void)
	{
		m_sHitObject[0] = '\n';
		m_dFiredTime = 0.0f;
		m_lvdVisitedPoints.clear();
	}

	void Serialize(FILE* pkLogFile);
	void Deserialize(FILE* pkLogFile);

private:
	
	double m_dFiredTime = 0.0; //SMB: initialized to avoid warning C26495
	vuList<vuVec3<double>> m_lvdVisitedPoints;
	char m_sHitObject[256] = { 0 };
};

#endif