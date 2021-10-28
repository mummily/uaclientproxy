/******************************************************************************
** uareaderwriterlock.h
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
** UaReaderWriterLock class allows acess to a resource for multiple reader but explicit acess for a writer.
**
******************************************************************************/
#ifndef UAREADERWRITERLOCK_H
#define UAREADERWRITERLOCK_H

#include <uabase.h>

class UaSemaphore;
class UaMutex;

/** @ingroup CppBaseLibraryClass
 *  @brief UaReaderWriterLock class is used to allow threads to synchronize access to a resource.
 *  The UaReaderWriterLock class provides read access to multiple consumers at a time.
 *  When a writer has access no other writers or readers can have access.
 *  It is not possible to create shallow copies of this Class.
 *  It is not possible to use the default constructor.
 */
class UABASE_EXPORT UaReaderWriterLock
{
    UA_DISABLE_COPY(UaReaderWriterLock);
public:
    UaReaderWriterLock(OpcUa_UInt16 parallelReadCount = 5);
    ~UaReaderWriterLock();

    void lockRead();
    void unlockRead();

    void lockWrite();
    void unlockWrite();

private:
    UaSemaphore* m_pSemaphore;
    UaMutex* m_pMutexWrite;
    int m_parallelReadCount;
};

#endif // UAREADERWRITERLOCK_H
