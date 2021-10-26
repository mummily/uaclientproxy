#include "CInoUARedClient.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"

CInoUARedClient::CInoUARedClient()
{
    m_pUAClientMaster = new CInoUAClient();
    m_pUAClientSlave = new CInoUAClient();
}

CInoUARedClient::~CInoUARedClient()
{
    DelAndNil(m_pUAClientMaster);
    DelAndNil(m_pUAClientSlave);
}

// ���������ӷ����
// ��ע����
bool CInoUARedClient::connect()
{
    UaStatus status;
    status = m_pUAClientMaster->connect();
    // m_pUAClientSlave->connect();

    return status.isGood();
    
}

// ������UA�ͻ��˶Ͽ��������������
// ʱ�䣺2021-10-21
// ��ע����
bool CInoUARedClient::disconnect()
{
    UaStatus status;
    if (m_pUAClientMaster->isConnected())
        status = m_pUAClientMaster->disconnect();
    if (m_pUAClientSlave->isConnected())
        status = m_pUAClientSlave->disconnect();

    return status.isGood();
}

// �������Ƿ����ӵ� OPC UA ������
// ��ע����
bool CInoUARedClient::isconnect()
{
    return m_pUAClientMaster->isConnected() != OpcUa_False;
}

// ������������UA�ͻ���
// ��ע����
CInoUAClient* CInoUARedClient::getUAClient()
{
    return m_pUAClientMaster;
}

// ���������ÿͻ�����������
// ��ע����
void CInoUARedClient::setConfiguration(CInoUAClientConfig* pConfigMaster, CInoUAClientConfig* pConfigSlave)
{
    m_pUAClientMaster->setConfiguration(pConfigMaster);
    m_pUAClientSlave->setConfiguration(pConfigSlave);
}

// ������������
// ʱ�䣺2021-10-21
// ��ע����
bool CInoUARedClient::read()
{
    CInoUAClient* pUAClient = getUAClient();
    return pUAClient->read().isGood();
}