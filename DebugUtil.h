#ifndef DEBUG_UTIL_MODULE_H
#define DEBUG_UTIL_MODULE_H

#include <cassert>

#define NULL 0
#define PI_OVER_180 0.0174532925
#define _180_OVER_PI 57.2957795

#if (_DEBUG)
	#define ASSERT(expr) assert(expr);
	#define DEBUG_PRINT(expr) printf(expr);
#else
	#define ASSERT(expr) ;
	#define DEBUG_PRINT(expr) ;
#endif

#endif
