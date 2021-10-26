#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

#define COMPANY_NAME "Inovance"
#define PRODUCT_NAME "FAMonitor"

using namespace UaClientSdk;

class CInoUAClientConfig
{
    UA_DISABLE_COPY(CInoUAClientConfig);

public:
    CInoUAClientConfig();
    virtual ~CInoUAClientConfig();

    // ��ȡ���ӺͻỰ����
    UaString getServerUrl() const;
    UaString getDiscoveryUrl() const;
    UaString getApplicationName() const;
    UaString getProductUri() const;
    OpcUa_Boolean getAutomaticReconnect() const;
    OpcUa_Boolean getRetryInitialConnect() const;

    // ��ȡ NodeId ��ֵ���б�
    UaNodeIdArray getNodesToRead() const;
    UaNodeIdArray getNodesToWrite() const;
    UaNodeIdArray getNodesToMonitor() const;
    UaVariantArray getWriteValues() const;
    UaNodeId getEventTypeToFilter() const;
    UaNodeIdArray getMethodsToCall() const;
    UaNodeIdArray getObjectsToCall() const;

    // ���ؿͻ�����������
    UaStatus loadConfiguration(const UaString& sConfigurationFile);

    // �����ļ��нṹ������֤�鲢���ػ򴴽��ͻ���֤�顣
    UaStatus setupSecurity(SessionSecurityInfo& sessionSecurityInfo);

    // �������� nodeId �������ռ������������ڲ� namespaceArray
    UaStatus updateNamespaceIndexes(const UaStringArray& namespaceArray);

private:
    // ���ӺͻỰ����
    UaString        m_applicationName;      // Ӧ������
    UaString        m_serverUrl;            // ����Url
    UaString        m_discoveryUrl;         // ����Url
    OpcUa_Boolean   m_bAutomaticReconnect;  // �Ƿ��Զ�����
    OpcUa_Boolean   m_bRetryInitialConnect; // �Ƿ��Գ�ʼ������

    // NamespaceArray �� NodeIds
    UaStringArray   m_namespaceArray;       // �����ռ�
    UaVariantArray  m_writeValues;          // д��ı�����ֵ
    UaNodeId        m_eventTypeToFilter;    // ���˵��¼�����

    UaNodeIdArray   m_nodesToRead;          // ��ȡ�ı���
    UaNodeIdArray   m_nodesToWrite;         // д��ı���
    UaNodeIdArray   m_nodesToMonitor;       // ���ӵı���
    UaNodeIdArray   m_methodsToCall;        // ����
    UaNodeIdArray   m_objectToCall;         // ����

    // ֤��
    UaString        m_certificateTrustListLocation;     // ���ε�֤��
    UaString        m_certificateRevocationListLocation;// ��ֹ��֤��
    UaString        m_issuersCertificatesLocation;      // ������֤��
    UaString        m_issuersRevocationListLocation;    // �����˽�ֹ֤��
    UaString        m_clientCertificate;                // �ͻ�֤��
    UaString        m_clientPrivateKey;                 // �ͻ�˽Կ
};
