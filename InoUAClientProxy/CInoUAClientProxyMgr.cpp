#include "CInoUAClientProxyMgr.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "CInoUAClientConnect.h"

CInoUAClientProxyMgr::CInoUAClientProxyMgr()
{
    init();
}

CInoUAClientProxyMgr::~CInoUAClientProxyMgr()
{
    // ����ͻ��˴������
    for (auto pi : m_mapClientProxy)
    {
        DelAndNil(pi.second);
    }

    cleanup();
}

// ��������ȡ�ͻ��˴���
// ��ע����
CInoUAClientConnect* CInoUAClientProxyMgr::GetClientProxy(emFAServerType serverType)
{
    // ��ȡ�ͻ��˴���
    CInoUAClientConnect* pClientProxy = nullptr;
    pClientProxy = m_mapClientProxy.at(serverType);
    if (nullptr == pClientProxy)
    {
        // �����ͻ��˴���
        pClientProxy = new CInoUAClientConnect(serverType);
        m_mapClientProxy[serverType] = pClientProxy;
    }

    return pClientProxy;
}

// ��������ʼ�� UA Stack ƽ̨��
// ��ע����
bool CInoUAClientProxyMgr::init()
{
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

// ���������� UA Stack ƽ̨��
// ��ע����
void CInoUAClientProxyMgr::cleanup()
{
    UaPlatformLayer::cleanup();
}