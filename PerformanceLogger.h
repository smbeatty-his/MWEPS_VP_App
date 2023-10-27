#ifndef PERFORMANCE_LOGGER_MODULE_H
#define PERFORMANCE_LOGGER_MODULE_H

#include <DebugUtil.h>

class PerformanceLogger
{

public:

	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)

		s_pkInstance = new PerformanceLogger();
	}

	static inline PerformanceLogger* GetInstance(void)
	{
		ASSERT(s_pkInstance)

		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		ASSERT(s_pkInstance)

		delete s_pkInstance;
	}

	void LogPerformanceData(const char* sFilename);
	void LoadPerformanceData(const char* sFilename);

	typedef struct binaryHeader
	{
		int		iTargetRecords;
		int		iShotRecords;
		int		iAimRecords;
	} BinaryHeader;

private:
	PerformanceLogger(void);
	~PerformanceLogger(void);

	BinaryHeader m_kHeader;
	static PerformanceLogger* s_pkInstance;
};

#endif