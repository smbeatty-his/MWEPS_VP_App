#ifndef SURFACE_TYPE_MODULE_H
#define SURFACE_TYPE_MODULE_H

#include <DebugUtil.h>
#include <vuVec3.h>

class SurfaceType
{
public:

	SurfaceType(void);
	~SurfaceType(void);

	const inline char* GetSoundName(void) const { return m_sSoundName; }
	const inline void SetSoundName(const char* sName) { strcpy(m_sSoundName, sName); }

	const inline char* GetEffectName(void) const { return m_sEffectName; }
	const inline void SetEffectName(const char* sName) { strcpy(m_sEffectName, sName); } 

	const inline vuVec3<double>& GetEffectScale(void) const { return m_vdEffectScale; }
	const inline void SetEffectScale(const vuVec3<double>& vdScale) { m_vdEffectScale = vdScale; }

private:

	char m_sSoundName[32];
	char m_sEffectName[32];
	vuVec3<double> m_vdEffectScale;
};

#endif