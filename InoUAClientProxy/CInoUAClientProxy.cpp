#include "CInoUAClientProxy.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "uadir.h"
#include "CInoUAClientConfig.h"
#include "CInoUARedClient.h"

CInoUAClientProxy::CInoUAClientProxy()
{
    init();

    #pragma TODO("加载所有的配置")
    CInoUAClientConfig* m_pUAClientConfig = new CInoUAClientConfig();
    UaStatus status = m_pUAClientConfig->loadConfiguration(getConfigPath().toUtf16());
    assert(status.isGood());
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
CInoUARedClient* CInoUAClientProxy::getRedClient(emFAServerType serverType)
{
    // 获取客户端代理
    CInoUARedClient* pClientProxy = nullptr;
    pClientProxy = m_mapClientConnect.at(serverType);
    if (nullptr == pClientProxy)
    {
        // 创建客户端代理
        pClientProxy = new CInoUARedClient();
        pClientProxy->setConfiguration(m_pUAClientConfig, m_pUAClientConfig);
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

// 描述：获取客户端配置
// 备注：无
UaUniString CInoUAClientProxy::getConfigPath()
{
#pragma TODO("配置的获取方式，需要以实际业务来定")
    wchar_t szFullPath[MAX_PATH];
    GetModuleFileNameW(NULL, szFullPath, sizeof(szFullPath));

    // 获取配置文件路径
    UaString sConfigFile(szFullPath);
        sConfigFile += "/../clientconfig.ini";

    UaDir dir(sConfigFile.toUtf8());
    return dir.canonicalPath();
}