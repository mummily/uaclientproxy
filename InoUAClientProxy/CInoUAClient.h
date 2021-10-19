#pragma once

#include "InoUAClientProxyExport.h"
#include "uabase.h"
#include "uaclientsdk.h"

class CInoUAClientSubscription;
class CInoUAClientConfig;
class CInoUAClientMgr;
using namespace UaClientSdk;

class INO_EXPORT CInoUAClient : public UaSessionCallback
{
    UA_DISABLE_COPY(CInoUAClient);

public:
    CInoUAClient();
    virtual ~CInoUAClient();

    friend class CInoUAClientMgr;

    virtual void connectionStatusChanged(OpcUa_UInt32 clientConnectionId, UaClient::ServerStatus serverStatus);

    // 设置一个我们用来获取连接参数和 NodeIds 的配置对象
    void setConfiguration(CInoUAClientConfig* pConfiguration);

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
    UaSession* m_pSession;
    CInoUAClientSubscription* m_pSampleSubscription;
    CInoUAClientConfig* m_pConfiguration;
    UaClient::ServerStatus  m_serverStatus;
    UaNodeIdArray           m_registeredNodes;
};

