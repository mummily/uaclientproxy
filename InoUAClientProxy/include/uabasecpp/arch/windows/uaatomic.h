/******************************************************************************
** uaatomic.h
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
** Atomic ops implementation using windows functions.
**
******************************************************************************/
#ifndef __UAATOMICWIN_H__
#define __UAATOMICWIN_H__

#if defined(_MSC_VER) && !defined(__cplusplus)
#define inline __inline
#endif

/** Atomically increments the int pointed to by pointer
 * @param pointer Pointer to the int to increment.
 * @return The value of pointer after the increment.
 */
inline int ua_atomic_increment(volatile int *pointer)
{
#ifdef _WIN32_WCE /* WinCE is little bit different */
    return InterlockedIncrement((LPLONG)pointer);
#else
    return InterlockedIncrement((LONG*)pointer);
#endif
}

/** Atomically decrements the int pointed to by pointer
 * @param pointer Pointer to the int to decrement.
 * @return The value of pointer after the decrement.
 */
inline int ua_atomic_decrement(volatile int *pointer)
{
#ifdef _WIN32_WCE /* WinCE is little bit different */
    return InterlockedDecrement((LPLONG)pointer);
#else
    return InterlockedDecrement((LONG*)pointer);
#endif
}

#endif /* __UAATOMICWIN_H__ */