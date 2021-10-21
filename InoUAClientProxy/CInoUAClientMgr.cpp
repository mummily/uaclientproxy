#include "CInoUAClientMgr.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"

CInoUAClientMgr::CInoUAClientMgr()
{
    m_pUAClientMaster = new CInoUAClient();
    m_pUAClientSlave = new CInoUAClient();
}

CInoUAClientMgr::~CInoUAClientMgr()
{
    DelAndNil(m_pUAClientMaster);
    DelAndNil(m_pUAClientSlave);
}

// 描述：连接服务端
// 备注：无
UaStatus CInoUAClientMgr::connect()
{
    UaStatus status;
    status = m_pUAClientMaster->connect();
    // m_pUAClientSlave->connect();

    return status;
}

// 描述：设置主UA客户端
// 备注：无
CInoUAClient* CInoUAClientMgr::getUAClient()
{
    return m_pUAClientMaster;
}

// 描述：设置客户端连接配置
// 备注：无
void CInoUAClientMgr::setConfiguration(CInoUAClientConfig* pConfiguration)
{
    m_pUAClientMaster->setConfiguration(pConfiguration);
    m_pUAClientSlave->setConfiguration(pConfiguration);
}

// 描述：读变量
// 时间：2021-10-21
// 备注：无
bool CInoUAClientMgr::read()
{
    CInoUAClient* pUAClient = getUAClient();
    return pUAClient->read().isGood();
}
