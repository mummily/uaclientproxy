#include "CInoUAClientProxyMgr.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "InoCommonDef.h"
#include "CInoUAClientProxy.h"

CInoUAClientProxyMgr::CInoUAClientProxyMgr()
{
    init();

    // �����ͻ��˴���
    m_pRtClientProxy = new CInoUAClientProxy(emFAServerType::RealTime);
    m_pIOClientProxy = new CInoUAClientProxy(emFAServerType::IO);
}

CInoUAClientProxyMgr::~CInoUAClientProxyMgr()
{
    // ����ͻ��˴������
    DelAndNil(m_pRtClientProxy);
    DelAndNil(m_pIOClientProxy);

    cleanup();
}

// ��������ȡ�ͻ��˴���
// ��ע����
CInoUAClientProxy* CInoUAClientProxyMgr::GetClientProxy(emFAServerType serverType)
{
    CInoUAClientProxy* pClientProxy = nullptr;
    switch (serverType)
    {
    case emFAServerType::RealTime:
        pClientProxy = m_pRtClientProxy;
        break;
    case emFAServerType::IO:
        pClientProxy = m_pIOClientProxy;
        break;
    }

    if (nullptr == pClientProxy)
        return nullptr;

    if (!pClientProxy->isconnect())
    {
        pClientProxy->connect();
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

// ��������ȡʵʱ����ͻ��˴���
// ��ע����
CInoUAClientProxy* CInoUAClientProxyMgr::GetRtClientProxy()
{
    return GetClientProxy(emFAServerType::RealTime);
}
