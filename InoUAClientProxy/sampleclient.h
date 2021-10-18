#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

class SampleSubscription;
class Configuration;
using namespace UaClientSdk;

class SampleClient : public UaSessionCallback
{
    UA_DISABLE_COPY(SampleClient);
public:
    SampleClient();
    virtual ~SampleClient();

    virtual void connectionStatusChanged(OpcUa_UInt32 clientConnectionId, UaClient::ServerStatus serverStatus);

    // 设置一个我们用来获取连接参数和 NodeIds 的配置对象
    void setConfiguration(Configuration* pConfiguration);

    OpcUa_Boolean isConnected() const;
    UaStatus connect(const UaString& sURL);
    // OPC UA 服务调用
    UaStatus discover();
    UaStatus connect();
    UaStatus connectSecure();
    UaStatus disconnect();
    UaStatus browseSimple();
    UaStatus browseContinuationPoint();
    UaStatus read();
    UaStatus write();
    UaStatus writeRegistered();
    UaStatus subscribe();
    UaStatus unsubscribe();
    UaStatus registerNodes();
    UaStatus unregisterNodes();
    UaStatus callMethods();

private:
    UaStatus browseInternal(const UaNodeId& nodeToBrowse, OpcUa_UInt32 maxReferencesToReturn);
    UaStatus connectInternal(const UaString& serverUrl, SessionSecurityInfo& sessionSecurityInfo);
    UaStatus writeInternal(const UaNodeIdArray& nodesToWrite, const UaVariantArray& valuesToWrite);
    UaStatus findSecureEndpoint(SessionSecurityInfo& sessionSecurityInfo);
    UaStatus checkServerCertificateTrust(SessionSecurityInfo& sessionSecurityInfo);
    UaStatus callMethodInternal(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId);
    void printBrowseResults(const UaReferenceDescriptions& referenceDescriptions);
    void printCertificateData(const UaByteString& serverCertificate);
    int userAcceptCertificate();

private:
    UaSession*              m_pSession;
    SampleSubscription*     m_pSampleSubscription;
    Configuration*          m_pConfiguration;
    UaClient::ServerStatus  m_serverStatus;
    UaNodeIdArray           m_registeredNodes;
};

