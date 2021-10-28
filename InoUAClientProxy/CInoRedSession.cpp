#include "CInoRedSession.h"
#include "CInoSession.h"
#include "InoCommonDef.h"

CInoRedSession::CInoRedSession()
{
    m_pSessionMaster = new CInoSession();
    m_pSessionSlave = new CInoSession();
}

CInoRedSession::~CInoRedSession()
{
    DelAndNil(m_pSessionMaster);
    DelAndNil(m_pSessionSlave);
}

// ���������ӷ����
// ��ע����
UaStatus CInoRedSession::connect()
{
    UaStatus status;
    status = m_pSessionMaster->connect();
    // m_pUAClientSlave->connect();

    return status;
    
}

// ������UA�ͻ��˶Ͽ��������������
// ʱ�䣺2021-10-21
// ��ע����
UaStatus CInoRedSession::disconnect()
{
    UaStatus status;
    if (m_pSessionMaster->isConnected())
        status = m_pSessionMaster->disconnect();
    if (m_pSessionSlave->isConnected())
        status = m_pSessionSlave->disconnect();

    return status;
}

// ������������UA�ͻ���
// ��ע����
CInoSession* CInoRedSession::getSession()
{
    return m_pSessionMaster;
}

// ���������ÿͻ�����������
// ��ע����
void CInoRedSession::setConfiguration(CInoSessionConfig* pConfigMaster, CInoSessionConfig* pConfigSlave)
{
    m_pSessionMaster->setConfiguration(pConfigMaster);
    m_pSessionSlave->setConfiguration(pConfigSlave);
}

// ������������
// ʱ�䣺2021-10-21
// ��ע����
bool CInoRedSession::read()
{
    CInoSession* pSession = getSession();
    return pSession->read().isGood();
}