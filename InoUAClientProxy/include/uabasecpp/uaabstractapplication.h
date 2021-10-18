/******************************************************************************
** uaabstractapplication.h
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
******************************************************************************/
#ifndef __UAABSTRACTAPPLICATION_H__
#define __UAABSTRACTAPPLICATION_H__

//#define USE_EVENTLOG

#include <uabase.h>
#include <uastring.h>

class UABASE_EXPORT UaAbstractApplication
{
    UA_DISABLE_COPY(UaAbstractApplication);
public:
    UaAbstractApplication();
    UaAbstractApplication(int argc, char* argv[], bool bRunAsService, const UaString &sApplicationName);
    virtual ~UaAbstractApplication();

    static int initEnvironment();
    static void cleanupEnvironment();

    // Main routine, calls main() of subclass
    virtual int run() = 0;

    /** System message level enumeration defining the trace level for system event log. */
    enum SystemMessageLevel
    {
        SystemMessageLevel_Error, /*!< Error level for system event log. */
        SystemMessageLevel_Warning, /*!< Warning level for system event log. */
        SystemMessageLevel_Info /*!< Info level for system event log. */
    };
    virtual void logSystemMessage(SystemMessageLevel traceLevel, const char *szMessage, ...) = 0;

protected:
    virtual int main() = 0;
    virtual bool shutdownFlag() const = 0;

    virtual int registerService() = 0;
    virtual int unregisterService() = 0;

    virtual int registerSyslog() = 0;
    virtual int unregisterSyslog() = 0;

    virtual int initSyslog() = 0;
    virtual int clearSyslog() = 0;

    virtual void registerSignalHandlers() = 0;

    int         m_argc;
    char      **m_argv;
    bool        m_bRunAsService;
    UaString    m_sApplicationName;
    bool        m_bShutdown;

    static UaAbstractApplication *s_pUaApplication;
};

#endif /* __UAABSTRACTAPPLICATION_H__ */
