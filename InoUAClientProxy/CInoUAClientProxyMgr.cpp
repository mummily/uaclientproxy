#include "CInoUAClientProxyMgr.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"

CInoUAClientProxyMgr::CInoUAClientProxyMgr()
{
    init();
}

CInoUAClientProxyMgr::~CInoUAClientProxyMgr()
{
    cleanup();
}

bool CInoUAClientProxyMgr::init()
{
    // 初始化 UA Stack 平台层
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

bool CInoUAClientProxyMgr::cleanup()
{
    // 清除客户端调用
    for (pair<string, CInoUAClient*> pi : m_mapClient)
    {
        DelAndNil(pi.second);
    }

    // 清理 UA Stack 平台层
    UaPlatformLayer::cleanup();
    return true;
}

bool CInoUAClientProxyMgr::connect(const string& sURL)
{
    CInoUAClient* pMyClient = new CInoUAClient();

    // 连接到 OPC UA 服务器
    UaStatus status = pMyClient->connect(sURL.c_str());
    if (!status.isGood())
        return false;

    m_mapClient[sURL] = pMyClient;

    return true;
}
