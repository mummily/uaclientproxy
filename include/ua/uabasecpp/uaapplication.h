/******************************************************************************
** uaapplication.h
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
#ifndef __UAAPPLICATION_H__
#define __UAAPPLICATION_H__

#include <uaabstractapplication.h>

#if defined(_WIN32_WCE)
#  define SHUTDOWN_SEQUENCE "Escape"
#else //defined(_WIN32_WCE)
// Uncomment the following line to use CTRL-C on Windows to shutdown
//#define UAAPPLICATION_USE_CTRLC_ON_WINDOWS
#  if defined(UAAPPLICATION_USE_CTRLC_ON_WINDOWS)
#    define SHUTDOWN_SEQUENCE "CTRL-C"
#  else //defined(UAAPPLICATION_USE_CTRLC_ON_WINDOWS)
#    define SHUTDOWN_SEQUENCE "x"
#  endif //defined(UAAPPLICATION_USE_CTRLC_ON_WINDOWS)
#endif //defined(_WIN32_WCE)

#ifndef WIN32_LEAN_AND_MEAN
/* Always define WIN32_LEAN_AND_MEAN to prevent windows.h from including
* winsock.h which leads to conflicts with winsock2.h */
#  define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

extern "C"
{
    void WINAPI UaApplication_SvcMain(DWORD, LPTSTR*);
    void WINAPI UaApplication_SvcCtrlHandler(DWORD);
#if defined(UAAPPLICATION_USE_CTRLC_ON_WINDOWS)
    BOOL WINAPI UaApplication_CtrlHandler(DWORD);
#endif //defined(UAAPPLICATION_USE_CTRLC_ON_WINDOWS)
}

class UABASE_EXPORT UaApplication : public UaAbstractApplication
{
    UA_DISABLE_COPY(UaApplication);
public:
    UaApplication();
    UaApplication(int argc, char* argv[], bool bRunAsService, const UaString &sApplicationName);
    virtual ~UaApplication();

    virtual int run();
    virtual void logSystemMessage(SystemMessageLevel traceLevel, const char *szMessage, ...);

    static UaString getApplicationPath();

protected:
    virtual int main() = 0;
    virtual bool shutdownFlag() const;

    virtual int registerService();
    virtual int unregisterService();

    virtual int registerSyslog();
    virtual int unregisterSyslog();

    virtual int initSyslog();
    virtual int clearSyslog();

    virtual void registerSignalHandlers();

    void setShutdownFlag(bool bShutdown);

private:
    TCHAR* getApplicationFilePath() const;
    TCHAR* getApplicationName() const;

    HANDLE m_hEventLog;

    friend void WINAPI UaApplication_SvcMain(DWORD, LPTSTR*);
    friend void WINAPI UaApplication_SvcCtrlHandler(DWORD);
#if defined(UAAPPLICATION_USE_CTRLC_ON_WINDOWS)
    friend BOOL WINAPI UaApplication_CtrlHandler(DWORD);
#endif //defined(UAAPPLICATION_USE_CTRLC_ON_WINDOWS)
};

#endif /* __UAAPPLICATION_H__ */
