#include "CInoUAClientProxyMgr.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "CInoUAClientProxy.h"

CInoUAClientProxyMgr::CInoUAClientProxyMgr()
{
    init();

    // 创建客户端代理
    m_pRtClientProxy = new CInoUAClientProxy(emFAServerType::RealTime);
    m_pIOClientProxy = new CInoUAClientProxy(emFAServerType::IO);
}

CInoUAClientProxyMgr::~CInoUAClientProxyMgr()
{
    // 清除客户端代理调用
    DelAndNil(m_pRtClientProxy);
    DelAndNil(m_pIOClientProxy);

    cleanup();
}

bool CInoUAClientProxyMgr::init()
{
    // 初始化 UA Stack 平台层
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

void CInoUAClientProxyMgr::cleanup()
{
    // 清理 UA Stack 平台层
    UaPlatformLayer::cleanup();
}

CInoUAClientProxy* CInoUAClientProxyMgr::GetRtClientProxy()
{
    if (!m_pRtClientProxy->isconnect())
    {
        m_pRtClientProxy->connect();
    }

    return m_pRtClientProxy;
}
