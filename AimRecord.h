#ifndef AIM_RECORD_MODULE_H
#define AIM_RECORD_MODULE_H

#include <vuVec2.h>
#include <vuVec3.h>

///////////////////////////////////////////////////////////////////////////////
///
/// @class AimRecord
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class AimRecord
{
public:

	AimRecord() {};
	~AimRecord() {};

	inline void SetAimTime(const double dAimTime) { m_dAimTime = dAimTime; };
	const inline double GetAimTime(void) const { return m_dAimTime; };
	const inline vuVec3<double>& GetStartPos(void) const { return m_vdStartPos; }; 
	inline void SetStartPos(const vuVec3<double>& pdStartPos) { m_vdStartPos = pdStartPos; };
	inline void SetAimPix(const vuVec2<double>& pdAimPix) { m_vdAimPix = pdAimPix; };
	const inline vuVec3<double>& GetEndPos(void) const { return m_vdEndPos; };
	inline void SetEndPos(const vuVec3<double>& pdEndPos) { m_vdEndPos = pdEndPos; };
	void Serialize(FILE* pkLogFile);
	void Deserialize(FILE* pkLogFile);

private:
	
	int m_iWeaponType = 0; //SMB: initialized to avoid warning C26495
	double m_dReceiveTime = 0.0; //SMB: initialized to avoid warning C26495
	double m_dAimTime = 0.0; //SMB: initialized to avoid warning C26495
	vuVec2<double> m_vdAimPix; //SMB: add X,Y pixels for Aim Point
	vuVec2<double> m_vdMousePos; //SMB: old code used Mouse Position, we use Laser Spot position
	vuVec3<double> m_vdStartPos;
	vuVec3<double> m_vdEndPos;
};

#endif
