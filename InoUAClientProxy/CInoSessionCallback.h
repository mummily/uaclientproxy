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

    // 连接状态变更回调函数
    virtual void connectionStatusChanged(OpcUa_UInt32 clientConnectionId, UaClient::ServerStatus serverStatus);

private:
    CInoSession* m_pSession = nullptr;
    UaClient::ServerStatus m_serverStatus;          // 客户端连接服务器状态：连接或重连
};
