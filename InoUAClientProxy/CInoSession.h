#pragma once

#include "InoExportDef.h"
#include "uaclientsdk.h"
#include "uasession.h"

using namespace UaClientSdk;

class UaSession;
class CInoSubscription;
class CInoSessionConfig;
class CInoRedSession;
class CInoSessionCallback;
class CInoSubscriptionCallback;
class INO_EXPORT CInoSession : public UaClientSdk::UaSession
{
    UA_DISABLE_COPY(CInoSession);

public:
    CInoSession();
    virtual ~CInoSession();

    friend class CInoRedSession;

    // ���ÿͻ���������Ϣ
    void setConfiguration(CInoSessionConfig* pConfiguration);
    // ���ҷ������������������Ϣ
    UaStatus discover(const UaString& sDiscoveryUrl);
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
    UaStatus read(const UaNodeIdArray& nodes);
    // ���������ļ����ڵ����дֵ
    UaStatus write(const UaNodeIdArray& nodes, const UaVariantArray& values);
    // ��ע��Ľڵ�д��ֵ
    UaStatus writeRegistered(const UaVariantArray& values);
    // �ڷ������ϴ������ĺͼ�����
    UaStatus subscribe();
    UaStatus createSubscriptionMonitors(bool bDeleteSubscription = false);
    // �ڷ��������˶�
    UaStatus unsubscribe();
    // ע��ڵ㣬Ĭ��ע������Ҫд��Ľڵ�
    UaStatus reRegisterNodes();
    UaStatus registerNodes(const UaNodeIdArray& nodesToRegister);
    // ע���ڵ�
    UaStatus unregisterNodes();

    // �ص�����ķ���
    using UaStatusArray = UaObjectArray<UaStatus>;
    UaStatus callMethodList(
        const UaNodeIdArray& objectNodeIds,
        const UaNodeIdArray& methodNodeIds,
        UaStatusArray& results);
    UaStatus callMethod(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId);

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
    // ���������referenceDescriptions
    void printBrowseResults(const UaReferenceDescriptions& referenceDescriptions);
    // ���֤����Ϣ
    void printCertificateData(const UaByteString& serverCertificate);
    // �ж��û�����֤��״̬
    int userAcceptCertificate();
    // �ڷ�������ɾ������
    UaStatus deleteSubscription();
    // �ڷ������ϴ�������
    UaStatus createSubscription();
    // �ڶ����д����ܼ�ص���Ŀ
    UaStatus createMonitoredItems(const UaNodeId& eventTypeToFilter);

private:
    CInoSessionCallback*            m_pSessionCallback = nullptr;  // �Ự�ص�
    UaClientSdk::UaSubscription*    m_pSubscription = nullptr;     // ����
    CInoSubscriptionCallback*       m_pSubscriptionCallback = nullptr; // ���Ļص�
    CInoSessionConfig*              m_pSessionConfig = nullptr;     // �ͻ�������
    UaNodeIdArray                   m_registeredNodes;              // ע��Ľڵ㣺Ĭ��������Ҫд��Ľڵ�
};

