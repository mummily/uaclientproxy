/*****************************************************************************
 *                                                                           *
 * Copyright (c) 2006-2018 Unified Automation GmbH. All rights reserved.     *
 *                                                                           *
 * Software License Agreement ("SLA") Version 2.7                            *
 *                                                                           *
 * Unless explicitly acquired and licensed from Licensor under another       *
 * license, the contents of this file are subject to the Software License    *
 * Agreement ("SLA") Version 2.7, or subsequent versions as allowed by the   *
 * SLA, and You may not copy or use this file in either source code or       *
 * executable form, except in compliance with the terms and conditions of    *
 * the SLA.                                                                  *
 *                                                                           *
 * All software distributed under the SLA is provided strictly on an "AS     *
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,       *
 * AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT      *
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR   *
 * PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific   *
 * language governing rights and limitations under the SLA.                  *
 *                                                                           *
 * The complete license agreement can be found here:                         *
 * http://unifiedautomation.com/License/SLA/2.7/                             *
 *                                                                           *
 * Project: Unified Automation OPC UA ANSI C Communication Stack             *
 *                                                                           *
 * This software is based in part on the ANSI C Stack of the OPC Foundation. *
 * Initial version of the ANSI C Stack was founded and copyrighted by OPC    *
 * Foundation, Inc.                                                          *
 * Copyright (C) 2008, 2014 OPC Foundation, Inc., All Rights Reserved.       *
 *****************************************************************************/

#ifndef _OpcUa_PlatformDefs_H_
#define _OpcUa_PlatformDefs_H_ 1

#define OPCUA_CONFIG_NO  0
#define OPCUA_CONFIG_YES !OPCUA_CONFIG_NO

#define OPCUA_CONFIG_ON  OPCUA_CONFIG_YES
#define OPCUA_CONFIG_OFF OPCUA_CONFIG_NO

#ifndef WIN32_LEAN_AND_MEAN
/* Always define WIN32_LEAN_AND_MEAN to prevent windows.h from including
 * winsock.h which leads to conflicts with winsock2.h */
# define WIN32_LEAN_AND_MEAN
#endif

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning( disable : 4001 )
#endif /* _MSC_VER */

/* System Headers */
#include <stdio.h>
#include <stdarg.h>

#ifdef _MSC_VER
  #pragma warning( pop )
  #pragma warning (disable: 4115)
  #pragma warning (disable: 4102)
#endif /* _MSC_VER */

#ifdef __cplusplus
# define OPCUA_BEGIN_EXTERN_C extern "C" {
# define OPCUA_END_EXTERN_C }
#else
# define OPCUA_BEGIN_EXTERN_C
# define OPCUA_END_EXTERN_C
#endif

/*============================================================================
* Types and Mapping
*===========================================================================*/

OPCUA_BEGIN_EXTERN_C

#define OPCUA_P_LITTLE_ENDIAN 1234
#define OPCUA_P_BIG_ENDIAN    4321
#define OPCUA_P_BYTE_ORDER OPCUA_P_LITTLE_ENDIAN

#define OPCUA_P_EXPORT __declspec(dllexport)
#define OPCUA_P_IMPORT __declspec(dllimport)

/* marks functions that need to be exported via functiontable */
#if defined(_UA_STACK_BUILD_DLL)
  #define OPCUA_EXPORT OPCUA_P_EXPORT
#else
  #define OPCUA_EXPORT
#endif

#define OPCUA_EXPORT_SYNC_SERVER_API OPCUA_EXPORT

#if defined(_UA_STACK_USE_DLL)
  #define OPCUA_IMPORT OPCUA_P_IMPORT
#else
  #define OPCUA_IMPORT
#endif

#if defined(_UA_STACK_BUILD_DLL)
    #define OPCUA_IMEXPORT OPCUA_P_EXPORT
#elif defined(_UA_STACK_USE_DLL)
    #define OPCUA_IMEXPORT OPCUA_P_IMPORT
#else
  /* build/using static lib */
  #define OPCUA_IMEXPORT
#endif

/* call exported functions by stdcall convention */
#if defined(_WIN32_WCE) || defined(__GNUC__)
  #define OPCUA_DLLCALL
#else
  #define OPCUA_DLLCALL __stdcall
#endif

/* calling convention used by stack functions that explicitely use cdecl */
#define OPCUA_CDECL __cdecl

/* used ie. for unlimited timespans */
#define OPCUA_INFINITE 0xFFFFFFFF

/* helper macro to convert a numeric define into a string (only use OPCUA_TOSTRING) */
#ifndef OPCUA_TOSTRING_HELP
# define OPCUA_TOSTRING_HELP(xNumber)  #xNumber
#endif

#ifndef OPCUA_TOSTRING
# define OPCUA_TOSTRING(xNumber) OPCUA_TOSTRING_HELP(xNumber)
#endif

/* Static (or static like) assertions (must accept sizeof()) */
#define OPCUA_P_STATIC_ASSERT(xExpression, xMessage) C_ASSERT(xExpression)

/* Macro for marking a function as deprecated. */
#if defined(_MSC_VER)
# define OPCUA_P_DEPRECATED(func) __declspec(deprecated("This function is deprecated, check documentation for replacements")) func
#elif defined(__GNUC__)
# define OPCUA_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
# if OPCUA_GCC_VERSION >= 40500
#  define OPCUA_P_DEPRECATED(func) func __attribute__ ((deprecated("This function is deprecated, check documentation for replacements")))
# else
#  define OPCUA_P_DEPRECATED(func) func __attribute__ ((deprecated))
# endif
#else
# define OPCUA_P_DEPRECATED(func) func
#endif

/* Macro to force checking the return values (missing error handling) */
#if defined(_MSC_VER)
# define OPCUA_P_WARN_UNUSED_RESULT _Check_return_
#elif defined(__GNUC__)
# define OPCUA_P_WARN_UNUSED_RESULT __attribute((__warn_unused_result__))
#else
# define OPCUA_P_WARN_UNUSED_RESULT
#endif

/*============================================================================
* Additional basic headers
*===========================================================================*/
#include <string.h>

/* get compiler name and version */
#include <opcua_p_compilerinfo.h>

/*============================================================================
* Additional basic headers
*===========================================================================*/
/* configuration switches */
#include "opcua_p_config.h"
#include <opcua_config.h>

/* basic type mapping */
#include "opcua_p_types.h"

/** @brief Additional information from the company, ie. internal revision number. */
#ifndef OPCUA_P_BUILDINFO_COMPILER
# define OPCUA_P_BUILDINFO_COMPILER                 OPCUA_P_COMPILERINFO
#endif /* OPCUA_P_BUILDINFO_COMPILER */

/** @brief Separator used between different fields in the version string. */
#ifndef OPCUA_P_VERSIONSTRING_SEPARATOR
# define OPCUA_P_VERSIONSTRING_SEPARATOR            "\\"
#endif

/** @brief The versionstring returned by OpcUa_P_GetVersion. */
#define OPCUA_P_VERSIONSTRING                       "PlatformName:"    OPCUA_P_BUILDINFO_PLATFORMNAME     OPCUA_P_VERSIONSTRING_SEPARATOR \
                                                    "SourceTimestamp:" OPCUA_P_BUILDINFO_SOURCE_TIMESTAMP OPCUA_P_VERSIONSTRING_SEPARATOR \
                                                    "BuildTimestamp:"  OPCUA_P_BUILDINFO_BUILD_TIMESTAMP  OPCUA_P_VERSIONSTRING_SEPARATOR \
                                                    "VendorName:"      OPCUA_P_BUILDINFO_VENDOR_NAME      OPCUA_P_VERSIONSTRING_SEPARATOR \
                                                    "VendorInfo:"      OPCUA_P_BUILDINFO_VENDOR_INFO      OPCUA_P_VERSIONSTRING_SEPARATOR \
                                                    "Compiler:"        OPCUA_P_BUILDINFO_COMPILER

/*============================================================================
 * Memory allocation functions.
 *
 * Note: Realloc and Free behave gracefully if passed a NULL pointer. Changing
 * these functions to a macro call to free will cause problems.
 *===========================================================================*/

/* shortcuts for often used memory functions */
#define OpcUa_Alloc(xSize)                              OpcUa_Memory_Alloc(xSize)
#define OpcUa_ReAlloc(xSrc, xSize)                      OpcUa_Memory_ReAlloc(xSrc, xSize)
#define OpcUa_Free(xSrc)                                OpcUa_Memory_Free(xSrc)
#define OpcUa_MemCpy(xDst, xDstSize, xSrc, xCount)      OpcUa_Memory_MemCpy(xDst, xDstSize, xSrc, xCount)
#define OpcUa_MemSet(xDst, xValue, xDstSize)            memset(xDst, xValue, xDstSize)
#define OpcUa_MemSetD(xDst, xValue, xDstSize)           memset(xDst, xValue, xDstSize)
#define OpcUa_MemMove(xDst, xSrc, xCount)               memmove(xDst, xSrc, xCount)
#define OpcUa_MemCmp(xBuf1, xBuf2, xBufSize)            memcmp(xBuf1, xBuf2, xBufSize)

/*============================================================================
 * String handling functions.
 *===========================================================================*/

/* mapping of ansi string functions on lib functions: */
#define OpcUa_StrCmpA(xStr1, xStr2)                     strcmp(xStr1, xStr2)
#define OpcUa_StrnCmpA(xStr1, xStr2, xCount)            strncmp(xStr1, xStr2, xCount)
#define OpcUa_StriCmpA(xStr1, xStr2)                    _stricmp(xStr1, xStr2)
#define OpcUa_StrinCmpA(xStr1, xStr2, xCount)           _strnicmp(xStr1, xStr2, xCount)
#define OpcUa_StrLenA(xStr)                             (OpcUa_UInt32)strlen(xStr)
#define OpcUa_StrChrA(xString, xChar)                   strchr(xString, (OpcUa_CharA)xChar)
#define OpcUa_StrrChrA(xString, xChar)                  strrchr(xString, (OpcUa_CharA)xChar)
#define OpcUa_StrStrA(xString, xSubstring)              strstr(xString, xSubstring)
#define OpcUa_StrnCpyA(xDest, xSrc, xCount)             strncpy(xDest, xSrc, xCount)
#define OpcUa_StrnCatA(xDest, xSrc, xCount)             strncat(xDest, xSrc, xCount)

#if OPCUA_USE_SAFE_FUNCTIONS
#define OpcUa_SPrintfA                                  sprintf_s
#else
#define OpcUa_SPrintfA                                  sprintf
#endif

#if OPCUA_USE_SAFE_FUNCTIONS
#define OpcUa_SnPrintfA                                 _snprintf_s
#else
#define OpcUa_SnPrintfA                                 _snprintf
#endif

#if OPCUA_USE_SAFE_FUNCTIONS
#define OpcUa_SScanfA                                   sscanf_s
#else
#define OpcUa_SScanfA                                   sscanf
#endif

/* shortcuts to OpcUa_String functions */
#define OpcUa_StrLen(xStr)                              OpcUa_String_StrLen(xStr)

/** Main application enty point macro. */
#define UA_MAIN_ENTRY_POINT(name) int main(int argc, char* argv[])

/** Support C99 __func__ keyword. */
#ifdef _MSC_VER
# define __func__ __FUNCTION__
#endif

OPCUA_END_EXTERN_C

#endif /* _OpcUa_PlatformDefs_H_ */
