#pragma once

#include "InoExportDef.h"
#include "uaclientsdk.h"

class UaSession;
class CInoUASubscription;
class CInoUAClientConfig;
class CInoUARedClient;
class CInoUASessionCallback;
using namespace UaClientSdk;

class INO_EXPORT CInoUAClient
{
    UA_DISABLE_COPY(CInoUAClient);

public:
    CInoUAClient();
    virtual ~CInoUAClient();

    friend class CInoUARedClient;

    // ���ÿͻ���������Ϣ
    void setConfiguration(CInoUAClientConfig* pConfiguration);
    // �ͻ����Ƿ�������״̬
    OpcUa_Boolean isConnected() const;
    // ���ҷ������������������Ϣ
    UaStatus discover();
    // �ǰ����ӷ�����
    UaStatus connect();
    // ��ȫ���ӷ�����
    UaStatus connectSecure();
    // �Ͽ�����
    UaStatus disconnect();
    // �Ӹ��ڵ�����ڵ�
    UaStatus browseSimple();
    // �������
    UaStatus browseContinuationPoint();
    // ���������ļ����ڵ���ж�ֵ
    UaStatus read();
    // ���������ļ����ڵ����дֵ
    UaStatus write();
    // ��ע��Ľڵ�д��ֵ
    UaStatus writeRegistered();
    // �ڷ������ϴ������ĺͼ�����
    UaStatus subscribe();
    // �ڷ��������˶�
    UaStatus unsubscribe();
    // ע��ڵ㣬Ĭ��ע������Ҫд��Ľڵ�
    UaStatus registerNodes();
    // ע���ڵ�
    UaStatus unregisterNodes();
    // �ص�����ķ����������޲���
    UaStatus callMethods();
    // �������� nodeId �������ռ������������ڲ� namespaceArray
    UaStatus updateNamespaceIndexes();

private:
    // �ӽڵ�nodeToBrowse�����ַ�ռ�
    UaStatus browseInternal(const UaNodeId& nodeToBrowse, OpcUa_UInt32 maxReferencesToReturn);
    // ���ӷ�������sessionConnectInfo�������ã�ʹ��sessionSecurityInfo���ӷ�����serverUrl
    UaStatus connectInternal(const UaString& serverUrl, SessionSecurityInfo& sessionSecurityInfo);
    // ���ڵ�nodesToWrite��д��valuesToWriteֵ
    UaStatus writeInternal(const UaNodeIdArray& nodesToWrite, const UaVariantArray& valuesToWrite);
    // �ڷ������ϲ��Ұ�ȫ�˵�
    UaStatus findSecureEndpoint(SessionSecurityInfo& sessionSecurityInfo);
    // ��֤������֤��
    UaStatus checkServerCertificateTrust(SessionSecurityInfo& sessionSecurityInfo);
    // �ص�����objectNodeId��methodNodeId�����������޲���
    UaStatus callMethodInternal(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId);
    // ���������referenceDescriptions
    void printBrowseResults(const UaReferenceDescriptions& referenceDescriptions);
    // ���֤����Ϣ
    void printCertificateData(const UaByteString& serverCertificate);
    // �ж��û�����֤��״̬
    int userAcceptCertificate();

private:
    UaClientSdk::UaSession* m_pSession = nullptr;                // �Ự
    CInoUASessionCallback* m_pSessionCallback = nullptr; // �Ự�ص�
    CInoUASubscription* m_pSubscription = nullptr;  // ����
    CInoUAClientConfig* m_pConfiguration = nullptr; // �ͻ�������
    UaNodeIdArray m_registeredNodes;                // ע��Ľڵ㣺Ĭ��������Ҫд��Ľڵ�
};

