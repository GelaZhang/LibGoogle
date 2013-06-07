#ifndef PORT_H_
#define PORT_H_

#include <tchar.h>
#include <Windows.h>

#include "base/basictypes.h"
#ifndef byte
typedef unsigned char byte;
#endif

#ifndef time64 
typedef uint64 time64;
#endif

#ifndef UTIL_LOG
#define UTIL_LOG(x, y)         _tprintf y
#define CORE_LOG(x,y)			UTIL_LOG(x,y)
#define OPT_LOG(x,y)			UTIL_LOG(x,y)
#define NET_LOG(x,y)			UTIL_LOG(x,y)
#define SERVICE_LOG(x,y)		UTIL_LOG(x,y)
#define REPORT_LOG(x,y)			UTIL_LOG(x,y)
#endif


#define ASSERT(expr, msg)                                                    \
	((expr) ? 0 : _tprintf(_T("%s"), msg))

#define ASSERT1(expr) ASSERT(expr, (_T("")))

// VERIFY executes but does not check expression
#define VERIFY(expr, msg) \
	do {                   \
	(expr);              \
	} while (0)

#define VERIFY1(expr) VERIFY(expr, (_T("")))

#define REPORT(x,y,z,r) (x)? 0 : _tprintf z

/**
* @return Always returns an error value.  If GetLastError is not ERROR_SUCCESS
*   the function returns an HRESULT value derived from GetLastError()
*/
inline HRESULT GetCurError() {
	return ::GetLastError() == ERROR_SUCCESS ?
E_FAIL : HRESULT_FROM_WIN32(::GetLastError());
}

#endif