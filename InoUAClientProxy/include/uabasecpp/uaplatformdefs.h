/******************************************************************************
** uaplatformdefs.h
**
** Copyright (c) 2006-2018 Unified Automation GmbH. All rights reserved.
**
** Software License Agreement ("SLA") Version 2.7
**
** Unless explicitly acquired and licensed from Licensor under another
** license, the contents of this file are subject to the Software License
** Agreement ("SLA") Version 2.7, or subsequent versions
** as allowed by the SLA, and You may not copy or use this file in either
** source code or executable form, except in compliance with the terms and
** conditions of the SLA.
**
** All software distributed under the SLA is provided strictly on an
** "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
** AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
** LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
** PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific
** language governing rights and limitations under the SLA.
**
** The complete license agreement can be found here:
** http://unifiedautomation.com/License/SLA/2.7/
**
** Project: C++ OPC SDK base module
**
** Win32 platform definitions.
**
******************************************************************************/
#ifndef UAPLATFORMDEFS_H_
#define UAPLATFORMDEFS_H_ 1

/* global define for win32 */
#ifdef _MSC_VER
#ifndef _UA_WIN32
    #define _UA_WIN32
#endif /* _UA_WIN32 */
#endif /* _MSC_VER */

#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#ifndef WIN32_LEAN_AND_MEAN
/* Always define WIN32_LEAN_AND_MEAN to prevent windows.h from including
 * winsock.h which leads to conflicts with winsock2.h */
# define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>
#ifdef __MINGW32__
# include <ole2.h>
#endif
#include <wtypes.h> // windows DATE definition

#ifdef _WIN32_WCE
    #define mktime wceex_mktime
    #define localtime wceex_localtime
    #pragma warning (disable : 4005)
    #include "wce_time.h"
    #include <altcecrt.h>
    #define NO_TIMEB 1
    #include "winsock2.h"
#endif

#include "math.h"
#include "opcua_platformdefs.h"
#include "opcua_types.h"
#include "stdio.h"
#include "assert.h"

#define UA_ASSERT(x) assert(x)
#define UA_GetHostname(x, y) gethostname(x, y)

#ifdef _WIN32_WCE
    #define uaDebug(x)
#else
    #define uaDebug(x) OutputDebugStringA(x)
#endif

#include "time.h"

#ifdef _UA_BASE_BUILD_DLL
    #define UABASE_EXPORT __declspec(dllexport)
#elif defined _UA_BASE_USE_DLL
    #define UABASE_EXPORT __declspec(dllimport)
#else
    #define UABASE_EXPORT
#endif

#include <tchar.h>
#define UA_swprintf _snwprintf

#define UA_wcsncasecmp _wcsnicmp

#if defined(_MSC_VER) // _MSC_VER 1300 = VS2003, 1400 = VS2005
#  define Ua_rename  rename
#  if defined(_WIN32_WCE)
   int Ua_rename(const char* oldname, const char* newname);
   int UA_unlink(const char* filename);
   unsigned int UA_strnlen(const char *str, unsigned int sizeInBytes);
#  elif _MSC_VER < 1400
#    define UA_unlink  unlink
     unsigned int UA_strnlen(const char *str, unsigned int sizeInBytes);
#    ifndef INT_MIN
#      define INT_MIN OpcUa_Int32_Min
#    endif
#    ifndef INT_MAX
#      define INT_MAX OpcUa_Int32_Max
#    endif
#  else
#    define UA_unlink  _unlink
#    define UA_strnlen  strnlen
#  endif /* _MSC_VER < 1400 */
#else
#   define Ua_rename  rename
#   define UA_unlink  _unlink
#   define UA_strnlen  strnlen
#endif

OpcUa_UInt32 UA_GetLastError();
OpcUa_Void UA_SetLastError(OpcUa_UInt32 nError);

// Unsigned short used for wide character strings
#ifdef _NATIVE_WCHAR_T_DEFINED
    typedef wchar_t UaUShort;
#else
    typedef unsigned short UaUShort;
#endif

/* define format string specifiers according to C99 inttypes.h */
#define OpcUa_PRIi8  "d"
#define OpcUa_PRIu8  "u"
#define OpcUa_PRIi16 "d"
#define OpcUa_PRIu16 "u"
#define OpcUa_PRIi32 "I32d"
#define OpcUa_PRIu32 "I32u"
#define OpcUa_PRIi64 "I64d"
#define OpcUa_PRIu64 "I64u"
#define OpcUa_PRIuS  "Iu"

#ifndef swprintf
    #define swprintf    _snwprintf
#endif
#ifndef snprintf
    #define snprintf    _snprintf
#endif
#ifndef wcsncasecmp
    #define wcsncasecmp _wcsnicmp
#endif

OpcUa_Int32 OpcUa_MsecTo(OpcUa_DateTime fromTime, OpcUa_DateTime toTime);

#if defined(_MSC_VER) || defined(__MINGW32__)
OpcUa_Int64 strtoll(char *start, char **end, int base);
OpcUa_UInt64 strtoull(char *start, char **end, int base);
#endif /* defined(_MSC_VER) || defined(__MINGW32__) */
DATE UaTimeToVariantTime(OpcUa_DateTime* pUaTime);
OpcUa_DateTime VariantTimeToUaTime(DATE *pdate);

class UaString;
class UaUniString;
class UaByteArray;

OpcUa_Boolean Utf8ToLocal8Bit(const UaString *pSource, UaByteArray &baLocal8Bit);
OpcUa_Boolean Utf16ToLocal8Bit(const UaUniString *pSource, UaByteArray &baLocal8Bit);

OpcUa_Boolean Local8BitToUtf8(const UaByteArray *pbaLocal8Bit, UaString &sUtf8);
OpcUa_Boolean Local8BitToUtf16(const UaByteArray *pbaLocal8Bit, UaUniString &sUtf16);

#define UA_SECS_BETWEEN_EPOCHS 11644473600
#define UA_SECS_TO_100NS          10000000 /* 10^7 */
#define UA_MSECS_TO_100NS            10000 /* 10^4 */

#if ((defined(_MSC_VER)) && !(_MSC_VER < 1400))
    #define UA_HOURS_TO_100NS (OpcUa_UInt64)36000000000i64
#else
    #define UA_HOURS_TO_100NS      36000000000ll
#endif

/* The SDK doesn't use strncat and strncpy. But applications might use it.
 * Uncomment the following define for test purpose to find all occurances of strncat and strncpy
 * during compilation.
 */
/*#define NO_STRN_FUNCTIONS*/
#ifdef NO_STRN_FUNCTIONS
# define strncpy(a,b,c) error
# define strncat(a,b,c) error
/* these functions are even more evil!!! */
# define strcpy(a,b) error
# define strcat(a,b) error
#endif

#endif /* UAPLATFORMDEFS_H_ */




