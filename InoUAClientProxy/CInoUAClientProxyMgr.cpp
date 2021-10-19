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

// 描述：获取客户端代理
// 备注：无
CInoUAClientProxy* CInoUAClientProxyMgr::GetClientProxy(emFAServerType serverType)
{
    CInoUAClientProxy* pClientProxy = nullptr;
    switch (serverType)
    {
    case emFAServerType::RealTime:
        pClientProxy = m_pRtClientProxy;
        break;
    case emFAServerType::IO:
        pClientProxy = m_pIOClientProxy;
        break;
    }

    if (nullptr == pClientProxy)
        return nullptr;

    if (!pClientProxy->isconnect())
    {
        pClientProxy->connect();
    }

    return pClientProxy;
}

// 描述：初始化 UA Stack 平台层
// 备注：无
bool CInoUAClientProxyMgr::init()
{
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

// 描述：清理 UA Stack 平台层
// 备注：无
void CInoUAClientProxyMgr::cleanup()
{
    UaPlatformLayer::cleanup();
}

// 描述：获取实时服务客户端代理
// 备注：无
CInoUAClientProxy* CInoUAClientProxyMgr::GetRtClientProxy()
{
    return GetClientProxy(emFAServerType::RealTime);
}
