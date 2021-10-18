#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

using namespace UaClientSdk;

class SampleClient : public UaSessionCallback
{
    UA_DISABLE_COPY(SampleClient);
public:
    SampleClient();
    virtual ~SampleClient();

    virtual void connectionStatusChanged(OpcUa_UInt32 clientConnectionId, UaClient::ServerStatus serverStatus);

    OpcUa_Boolean isConnected() const;
    UaStatus connect(const UaString& sURL);
    UaStatus disconnect();
    UaStatus read();

private:
    UaSession* m_pSession;
};

