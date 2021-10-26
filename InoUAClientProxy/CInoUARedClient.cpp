#include "CInoUARedClient.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"

CInoUARedClient::CInoUARedClient()
{
    m_pUAClientMaster = new CInoUAClient();
    m_pUAClientSlave = new CInoUAClient();
}

CInoUARedClient::~CInoUARedClient()
{
    DelAndNil(m_pUAClientMaster);
    DelAndNil(m_pUAClientSlave);
}

// 描述：连接服务端
// 备注：无
bool CInoUARedClient::connect()
{
    UaStatus status;
    status = m_pUAClientMaster->connect();
    // m_pUAClientSlave->connect();

    return status.isGood();
    
}

// 描述：UA客户端断开与服务器的连接
// 时间：2021-10-21
// 备注：无
bool CInoUARedClient::disconnect()
{
    UaStatus status;
    if (m_pUAClientMaster->isConnected())
        status = m_pUAClientMaster->disconnect();
    if (m_pUAClientSlave->isConnected())
        status = m_pUAClientSlave->disconnect();

    return status.isGood();
}

// 描述：是否连接到 OPC UA 服务器
// 备注：无
bool CInoUARedClient::isconnect()
{
    return m_pUAClientMaster->isConnected() != OpcUa_False;
}

// 描述：设置主UA客户端
// 备注：无
CInoUAClient* CInoUARedClient::getUAClient()
{
    return m_pUAClientMaster;
}

// 描述：设置客户端连接配置
// 备注：无
void CInoUARedClient::setConfiguration(CInoUAClientConfig* pConfigMaster, CInoUAClientConfig* pConfigSlave)
{
    m_pUAClientMaster->setConfiguration(pConfigMaster);
    m_pUAClientSlave->setConfiguration(pConfigSlave);
}

// 描述：读变量
// 时间：2021-10-21
// 备注：无
bool CInoUARedClient::read()
{
    CInoUAClient* pUAClient = getUAClient();
    return pUAClient->read().isGood();
}