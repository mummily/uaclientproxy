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

    // 连接状态变更回调函数
    virtual void connectionStatusChanged(OpcUa_UInt32 clientConnectionId, UaClient::ServerStatus serverStatus);

private:
    CInoUAClient* m_pUAClient = nullptr;
    UaClient::ServerStatus m_serverStatus;          // 客户端连接服务器状态：连接或重连
};
