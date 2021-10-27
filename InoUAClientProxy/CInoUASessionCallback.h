#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

using namespace UaClientSdk;

class CInoUAClient;
class CInoUASessionCallback : public UaSessionCallback
{
    UA_DISABLE_COPY(CInoUASessionCallback);

public:
    CInoUASessionCallback(CInoUAClient* pUAClient);
    virtual ~CInoUASessionCallback();

    // ����״̬����ص�����
    virtual void connectionStatusChanged(OpcUa_UInt32 clientConnectionId, UaClient::ServerStatus serverStatus);

private:
    CInoUAClient* m_pUAClient = nullptr;
    UaClient::ServerStatus m_serverStatus;          // �ͻ������ӷ�����״̬�����ӻ�����
};
