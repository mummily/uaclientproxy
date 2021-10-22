#include "CInoUAClientProxyMgr.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "CInoUAClientProxy.h"

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
CInoUAClientProxy* CInoUAClientProxyMgr::GetClientProxy(emFAServerType serverType)
{
    // ��ȡ�ͻ��˴���
    CInoUAClientProxy* pClientProxy = nullptr;
    pClientProxy = m_mapClientProxy.at(serverType);
    if (nullptr == pClientProxy)
    {
        // �����ͻ��˴���
        pClientProxy = new CInoUAClientProxy(serverType);
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