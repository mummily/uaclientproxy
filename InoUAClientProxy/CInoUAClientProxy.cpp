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

// ���������ӵ� OPC UA ������
// ��ע����
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

// �������Ƿ����ӵ� OPC UA ������
// ��ע����
bool CInoUAClientProxy::isconnect()
{
    CInoUAClient* pUAClient = m_pUAClientMgr->getUAClient();
    return pUAClient->isConnected() != OpcUa_False;
}

// ��������ȡ�ͻ�������
// ��ע����
UaUniString CInoUAClientProxy::GetConfigPath()
{
    wchar_t szFullPath[MAX_PATH];
    GetModuleFileNameW(NULL, szFullPath, sizeof(szFullPath));

    // ��ȡ�����ļ�·��
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