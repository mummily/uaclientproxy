#include "CInoUAClientProxy.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "CInoUAClientConnect.h"

CInoUAClientProxy::CInoUAClientProxy()
{
    init();
}

CInoUAClientProxy::~CInoUAClientProxy()
{
    // 清除客户端代理调用
    for (auto pi : m_mapClientConnect)
    {
        DelAndNil(pi.second);
    }

    cleanup();
}

// 描述：获取客户端代理
// 备注：无
CInoUAClientConnect* CInoUAClientProxy::GetClientConnect(emFAServerType serverType)
{
    // 获取客户端代理
    CInoUAClientConnect* pClientProxy = nullptr;
    pClientProxy = m_mapClientConnect.at(serverType);
    if (nullptr == pClientProxy)
    {
        // 创建客户端代理
        pClientProxy = new CInoUAClientConnect(serverType);
        m_mapClientConnect[serverType] = pClientProxy;
    }

    return pClientProxy;
}

// 描述：初始化 UA Stack 平台层
// 备注：无
bool CInoUAClientProxy::init()
{
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

// 描述：清理 UA Stack 平台层
// 备注：无
void CInoUAClientProxy::cleanup()
{
    UaPlatformLayer::cleanup();
}