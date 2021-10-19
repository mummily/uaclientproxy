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

bool CInoUAClientProxyMgr::init()
{
    // ��ʼ�� UA Stack ƽ̨��
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

void CInoUAClientProxyMgr::cleanup()
{
    // ���� UA Stack ƽ̨��
    UaPlatformLayer::cleanup();
}

CInoUAClientProxy* CInoUAClientProxyMgr::GetRtClientProxy()
{
    if (!m_pRtClientProxy->isconnect())
    {
        m_pRtClientProxy->connect();
    }

    return m_pRtClientProxy;
}
