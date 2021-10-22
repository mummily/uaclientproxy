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
    // ����ͻ��˴������
    for (auto pi : m_mapClientConnect)
    {
        DelAndNil(pi.second);
    }

    cleanup();
}

// ��������ȡ�ͻ��˴���
// ��ע����
CInoUAClientConnect* CInoUAClientProxy::GetClientConnect(emFAServerType serverType)
{
    // ��ȡ�ͻ��˴���
    CInoUAClientConnect* pClientProxy = nullptr;
    pClientProxy = m_mapClientConnect.at(serverType);
    if (nullptr == pClientProxy)
    {
        // �����ͻ��˴���
        pClientProxy = new CInoUAClientConnect(serverType);
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