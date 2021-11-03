#include "InoSessionGroup.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "uadir.h"
#include "InoSessionConfig.h"
#include "InoRedSession.h"

InoSessionGroup::InoSessionGroup()
{
    init();

    #pragma TODO("加载所有的配置")
    /*CInoSessionConfig* */m_pSessionConfig = new InoSessionConfig();
    UaStatus status = m_pSessionConfig->loadConfiguration(getConfigPath().toUtf16());
    assert(status.isGood());
}

InoSessionGroup::~InoSessionGroup()
{
    // 清除客户端代理调用
    for (auto pi : m_mapRedSession)
    {
        DelAndNil(pi.second);
    }

    cleanup();
}

// 描述：获取客户端代理
// 备注：无
InoRedSession* InoSessionGroup::getRedSession(emFAServerType serverType)
{
    // 获取客户端代理
    InoRedSession* pRedSession = nullptr;
    auto itFind = m_mapRedSession.find(serverType);
    if (m_mapRedSession.end() == itFind)
    {
        // 创建客户端代理
        pRedSession = new InoRedSession();
        pRedSession->setConfiguration(m_pSessionConfig, m_pSessionConfig);
        m_mapRedSession[serverType] = pRedSession;
    }

    return pRedSession;
}

// 描述：初始化 UA Stack 平台层
// 备注：无
bool InoSessionGroup::init()
{
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

// 描述：清理 UA Stack 平台层
// 备注：无
void InoSessionGroup::cleanup()
{
    UaPlatformLayer::cleanup();
}

// 描述：获取客户端配置
// 备注：无
UaUniString InoSessionGroup::getConfigPath()
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