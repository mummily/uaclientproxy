#include "CInoSessionGroup.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "uadir.h"
#include "CInoSessionConfig.h"
#include "CInoRedSession.h"

CInoSessionGroup::CInoSessionGroup()
{
    init();

    #pragma TODO("�������е�����")
    /*CInoSessionConfig* */m_pSessionConfig = new CInoSessionConfig();
    UaStatus status = m_pSessionConfig->loadConfiguration(getConfigPath().toUtf16());
    assert(status.isGood());
}

CInoSessionGroup::~CInoSessionGroup()
{
    // ����ͻ��˴������
    for (auto pi : m_mapRedSession)
    {
        DelAndNil(pi.second);
    }

    cleanup();
}

// ��������ȡ�ͻ��˴���
// ��ע����
CInoRedSession* CInoSessionGroup::getRedSession(emFAServerType serverType)
{
    // ��ȡ�ͻ��˴���
    CInoRedSession* pRedSession = nullptr;
    auto itFind = m_mapRedSession.find(serverType);
    if (m_mapRedSession.end() == itFind)
    {
        // �����ͻ��˴���
        pRedSession = new CInoRedSession();
        pRedSession->setConfiguration(m_pSessionConfig, m_pSessionConfig);
        m_mapRedSession[serverType] = pRedSession;
    }

    return pRedSession;
}

// ��������ʼ�� UA Stack ƽ̨��
// ��ע����
bool CInoSessionGroup::init()
{
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

// ���������� UA Stack ƽ̨��
// ��ע����
void CInoSessionGroup::cleanup()
{
    UaPlatformLayer::cleanup();
}

// ��������ȡ�ͻ�������
// ��ע����
UaUniString CInoSessionGroup::getConfigPath()
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