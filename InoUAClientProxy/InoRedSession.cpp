#include "InoRedSession.h"
#include "InoSession.h"
#include "InoCommonDef.h"
#include "uaarraytemplates.h"

InoRedSession::InoRedSession()
{
    m_pSessionMaster = new InoSession();
    m_pSessionSlave = new InoSession();
}

InoRedSession::~InoRedSession()
{
    DelAndNil(m_pSessionMaster);
    DelAndNil(m_pSessionSlave);
}

// 描述：连接服务端
// 备注：无
UaStatus InoRedSession::connect(const UaString& serverUrl1, const UaString& serverUrl2)
{
    UaStatus status;
    status = m_pSessionMaster->connect(serverUrl1);
    // m_pUAClientSlave->connect();

    return status;
    
}

// 描述：UA客户端断开与服务器的连接
// 时间：2021-10-21
// 备注：无
UaStatus InoRedSession::disconnect()
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
InoSession* InoRedSession::getSession()
{
    return m_pSessionMaster;
}

// 描述：设置客户端连接配置
// 备注：无
void InoRedSession::setConfiguration(InoSessionConfig* pConfigMaster, InoSessionConfig* pConfigSlave)
{
    m_pSessionMaster->setConfiguration(pConfigMaster);
    m_pSessionSlave->setConfiguration(pConfigSlave);
}

// 描述：读变量
// 时间：2021-10-21
// 备注：无
bool InoRedSession::read(const UaNodeIdArray& nodes)
{
    InoSession* pSession = getSession();
    UaDataValues values;
    return pSession->read(nodes, values).isGood();
}