#ifndef AAR_MANAGER_MODULE_H
#define AAR_MANAGER_MODULE_H

#include <DebugUtil.h>

///////////////////////////////////////////////////////////////////////////////
///
/// @class AARManager
///
///	@brief
///
///////////////////////////////////////////////////////////////////////////////

class AARManager
{
public:

	static inline AARManager* GetInstance(void) 
	{ 
		ASSERT(s_pkInstance)
		return s_pkInstance; 
	}

	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new AARManager();
	}

	static void Shutdown(void);

	const inline bool DisplayAimVectors(void) const { return m_bDisplayAimVectors; }
	const inline bool IsReviewActive(void) const { return m_bReviewActive; }
	inline void SetReviewActive(bool bReviewActive) { m_bReviewActive = bReviewActive; }
	void Update(void);
	void Reset(void);

private:

	AARManager(void);
	~AARManager(void);

	bool m_bDisplayAimVectors;
	bool m_bReviewActive;
	static AARManager* s_pkInstance;
};

#endif