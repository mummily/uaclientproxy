#include "CInoUAClientProxy.h"
#include "CInoUAClientMgr.h"
#include "statuscode.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"

CInoUAClientProxy::CInoUAClientProxy(emFAServerType _emFAServerType)
{
    m_pUAClientMgr = new CInoUAClientMgr(_emFAServerType);
}

CInoUAClientProxy::~CInoUAClientProxy()
{
    DelAndNil(m_pUAClientMgr);
}

// 描述：连接到 OPC UA 服务器
// 备注：无
bool CInoUAClientProxy::connect()
{
    UaStatus status = m_pUAClientMgr->getUAClient()->connect();
    return status.isGood();
}

// 描述：是否连接到 OPC UA 服务器
// 备注：无
bool CInoUAClientProxy::isconnect()
{
    return m_pUAClientMgr->getUAClient()->isConnected() != OpcUa_False;
}
