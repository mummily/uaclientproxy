#include "CInoUAClientProxyMgr.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "CInoUAClientProxy.h"

CInoUAClientProxyMgr::CInoUAClientProxyMgr()
{
    init();
}

CInoUAClientProxyMgr::~CInoUAClientProxyMgr()
{
    // 清除客户端代理调用
    for (auto pi : m_mapClientProxy)
    {
        DelAndNil(pi.second);
    }

    cleanup();
}

// 描述：获取客户端代理
// 备注：无
CInoUAClientProxy* CInoUAClientProxyMgr::GetClientProxy(emFAServerType serverType)
{
    // 获取客户端代理
    CInoUAClientProxy* pClientProxy = nullptr;
    pClientProxy = m_mapClientProxy.at(serverType);
    if (nullptr == pClientProxy)
    {
        // 创建客户端代理
        pClientProxy = new CInoUAClientProxy(serverType);
        m_mapClientProxy[serverType] = pClientProxy;
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