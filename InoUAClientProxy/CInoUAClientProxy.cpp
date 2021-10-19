#include "CInoUAClientProxy.h"
#include "CInoUAClientMgr.h"
#include "statuscode.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"

CInoUAClientProxy::CInoUAClientProxy(emFAServerType _emFAServerType)
{
    m_pUAClientMgr = new CInoUAClientMgr(_emFAServerType);
}

CInoUAClientProxy::~CInoUAClientProxy()
{
    DelAndNil(m_pUAClientMgr);
}

// ���������ӵ� OPC UA ������
// ��ע����
bool CInoUAClientProxy::connect()
{
    UaStatus status = m_pUAClientMgr->getUAClient()->connect();
    return status.isGood();
}

// �������Ƿ����ӵ� OPC UA ������
// ��ע����
bool CInoUAClientProxy::isconnect()
{
    return m_pUAClientMgr->getUAClient()->isConnected() != OpcUa_False;
}
