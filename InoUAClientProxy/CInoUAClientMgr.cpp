#include "CInoUAClientMgr.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"

CInoUAClientMgr::CInoUAClientMgr()
{
    m_pUAClientMaster = new CInoUAClient();
    m_pUAClientSlave = new CInoUAClient();
}

CInoUAClientMgr::~CInoUAClientMgr()
{
    DelAndNil(m_pUAClientMaster);
    DelAndNil(m_pUAClientSlave);
}

// ���������ӷ����
// ��ע����
UaStatus CInoUAClientMgr::connect()
{
    UaStatus status;
    status = m_pUAClientMaster->connect();
    // m_pUAClientSlave->connect();

    return status;
}

// ������������UA�ͻ���
// ��ע����
CInoUAClient* CInoUAClientMgr::getUAClient()
{
    return m_pUAClientMaster;
}

// ���������ÿͻ�����������
// ��ע����
void CInoUAClientMgr::setConfiguration(CInoUAClientConfig* pConfiguration)
{
    m_pUAClientMaster->setConfiguration(pConfiguration);
    m_pUAClientSlave->setConfiguration(pConfiguration);
}
