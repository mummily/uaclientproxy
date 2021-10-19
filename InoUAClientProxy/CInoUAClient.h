#pragma once

#include "InoExportDef.h"
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
    // 设置配置信息
    void setConfiguration(CInoUAClientConfig* pConfiguration);

    OpcUa_Boolean isConnected() const;
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
    UaSession* m_pSession = nullptr;
    CInoUAClientSubscription* m_pSubscription = nullptr;
    CInoUAClientConfig* m_pConfiguration = nullptr;
    UaClient::ServerStatus m_serverStatus;
    UaNodeIdArray m_registeredNodes;
};

