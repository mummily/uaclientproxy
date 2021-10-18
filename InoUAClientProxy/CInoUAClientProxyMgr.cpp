#include "CInoUAClientProxyMgr.h"

#include "uaplatformlayer.h"
#include "statuscode.h"
#include "sampleclient.h"
#include "CommonDef.h"

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
    // ��ʼ�� UA Stack ƽ̨��
    int iOk = UaPlatformLayer::init();
    assert(iOk != -1);
    return true;
}

bool CInoUAClientProxyMgr::cleanup()
{
    // ����ͻ��˵���
    for (pair<string, SampleClient*> pi : m_mapClient)
    {
        DelAndNil(pi.second);
    }

    // ���� UA Stack ƽ̨��
    UaPlatformLayer::cleanup();
    return true;
}

bool CInoUAClientProxyMgr::connect(const string& sURL)
{
    SampleClient* pMyClient = new SampleClient();

    // ���ӵ� OPC UA ������
    UaStatus status = pMyClient->connect(sURL.c_str());
    if (!status.isGood())
        return false;

    m_mapClient[sURL] = pMyClient;

    return true;
}
