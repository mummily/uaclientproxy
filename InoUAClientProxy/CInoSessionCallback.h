#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

using namespace UaClientSdk;

class CInoSession;
class CInoSessionCallback : public UaSessionCallback
{
    UA_DISABLE_COPY(CInoSessionCallback);

public:
    CInoSessionCallback(CInoSession* pSession);
    virtual ~CInoSessionCallback();

    // ����״̬����ص�����
    virtual void connectionStatusChanged(OpcUa_UInt32 clientConnectionId, UaClient::ServerStatus serverStatus);

private:
    CInoSession* m_pSession = nullptr;
    UaClient::ServerStatus m_serverStatus;          // �ͻ������ӷ�����״̬�����ӻ�����
};
