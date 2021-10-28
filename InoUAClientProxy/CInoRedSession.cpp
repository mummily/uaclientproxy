#include "CInoRedSession.h"
#include "CInoSession.h"
#include "InoCommonDef.h"

CInoRedSession::CInoRedSession()
{
    m_pSessionMaster = new CInoSession();
    m_pSessionSlave = new CInoSession();
}

CInoRedSession::~CInoRedSession()
{
    DelAndNil(m_pSessionMaster);
    DelAndNil(m_pSessionSlave);
}

// 描述：连接服务端
// 备注：无
UaStatus CInoRedSession::connect()
{
    UaStatus status;
    status = m_pSessionMaster->connect();
    // m_pUAClientSlave->connect();

    return status;
    
}

// 描述：UA客户端断开与服务器的连接
// 时间：2021-10-21
// 备注：无
UaStatus CInoRedSession::disconnect()
{
    UaStatus status;
    if (m_pSessionMaster->isConnected())
        status = m_pSessionMaster->disconnect();
    if (m_pSessionSlave->isConnected())
        status = m_pSessionSlave->disconnect();

    return status;
}

// 描述：设置主UA客户端
// 备注：无
CInoSession* CInoRedSession::getSession()
{
    return m_pSessionMaster;
}

// 描述：设置客户端连接配置
// 备注：无
void CInoRedSession::setConfiguration(CInoSessionConfig* pConfigMaster, CInoSessionConfig* pConfigSlave)
{
    m_pSessionMaster->setConfiguration(pConfigMaster);
    m_pSessionSlave->setConfiguration(pConfigSlave);
}

// 描述：读变量
// 时间：2021-10-21
// 备注：无
bool CInoRedSession::read()
{
    CInoSession* pSession = getSession();
    return pSession->read().isGood();
}