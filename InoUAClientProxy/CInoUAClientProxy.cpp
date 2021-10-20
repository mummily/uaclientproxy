#include "CInoUAClientProxy.h"
#include "CInoUAClientMgr.h"
#include "statuscode.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"
#include "CInoUAClientConfig.h"
#include "uaunistring.h"
#include "uadir.h"

CInoUAClientProxy::CInoUAClientProxy(emFAServerType serverType)
    : m_emFAServerType(serverType)
{
    m_pUAClientMgr = new CInoUAClientMgr();
}

CInoUAClientProxy::~CInoUAClientProxy()
{
    DelAndNil(m_pUAClientMgr);
    DelAndNil(m_pUAClientConfig);
}

// 描述：连接到 OPC UA 服务器
// 备注：无
bool CInoUAClientProxy::connect()
{
    if (nullptr == m_pUAClientConfig)
    {
        m_pUAClientConfig = new CInoUAClientConfig();
        UaStatus status = m_pUAClientConfig->loadConfiguration(GetConfigPath().toUtf16());
        assert(status.isGood());
    }

    m_pUAClientMgr->setConfiguration(m_pUAClientConfig);
    UaStatus status = m_pUAClientMgr->connect();
    return status.isGood();
}

// 描述：是否连接到 OPC UA 服务器
// 备注：无
bool CInoUAClientProxy::isconnect()
{
    CInoUAClient* pUAClient = m_pUAClientMgr->getUAClient();
    return pUAClient->isConnected() != OpcUa_False;
}

// 描述：获取客户端配置
// 备注：无
UaUniString CInoUAClientProxy::GetConfigPath()
{
    wchar_t szFullPath[MAX_PATH];
    GetModuleFileNameW(NULL, szFullPath, sizeof(szFullPath));

    // 获取配置文件路径
    UaString sConfigFile(szFullPath);
    switch (m_emFAServerType)
    {
    case emFAServerType::RealTime:
        sConfigFile += "/../rtconfig.ini";
        break;
    case emFAServerType::IO:
        sConfigFile += "/../ioconfig.ini";
        break;
    }

    UaDir dir(sConfigFile.toUtf8());
    return dir.canonicalPath();
}