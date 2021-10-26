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

    #pragma TODO("�������е�����")
    CInoUAClientConfig* m_pUAClientConfig = new CInoUAClientConfig();
    UaStatus status = m_pUAClientConfig->loadConfiguration(getConfigPath().toUtf16());
    assert(status.isGood());
}

CInoUAClientProxy::~CInoUAClientProxy()
{
    // ����ͻ��˴������
    for (auto pi : m_mapClientConnect)
    {
        DelAndNil(pi.second);
    }

    cleanup();
}

// ��������ȡ�ͻ��˴���
// ��ע����
CInoUARedClient* CInoUAClientProxy::getRedClient(emFAServerType serverType)
{
    // ��ȡ�ͻ��˴���
    CInoUARedClient* pClientProxy = nullptr;
    pClientProxy = m_mapClientConnect.at(serverType);
    if (nullptr == pClientProxy)
    {
        // �����ͻ��˴���
        pClientProxy = new CInoUARedClient();
        pClientProxy->setConfiguration(m_pUAClientConfig, m_pUAClientConfig);
        m_mapClientConnect[serverType] = pClientProxy;
    }

    return pClientProxy;
}

// ��������ʼ�� UA Stack ƽ̨��
// ��ע����
bool CInoUAClientProxy::init()
{
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

// ���������� UA Stack ƽ̨��
// ��ע����
void CInoUAClientProxy::cleanup()
{
    UaPlatformLayer::cleanup();
}

// ��������ȡ�ͻ�������
// ��ע����
UaUniString CInoUAClientProxy::getConfigPath()
{
#pragma TODO("���õĻ�ȡ��ʽ����Ҫ��ʵ��ҵ������")
    wchar_t szFullPath[MAX_PATH];
    GetModuleFileNameW(NULL, szFullPath, sizeof(szFullPath));

    // ��ȡ�����ļ�·��
    UaString sConfigFile(szFullPath);
        sConfigFile += "/../clientconfig.ini";

    UaDir dir(sConfigFile.toUtf8());
    return dir.canonicalPath();
}