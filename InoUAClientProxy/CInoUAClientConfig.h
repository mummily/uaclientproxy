#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

#define COMPANY_NAME "UnifiedAutomation"
#define PRODUCT_NAME "GettingStartedClient"

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

    // ���ļ�����������������Ӳ�����NamespaceArray �� NodeIds
    UaStatus loadConfiguration(const UaString& sConfigurationFile);

    // �����ļ��нṹ������֤�鲢���ػ򴴽��ͻ���֤�顣
    UaStatus setupSecurity(SessionSecurityInfo& sessionSecurityInfo);

    // �������� nodeId �������ռ������������ڲ� namespaceArray
    UaStatus updateNamespaceIndexes(const UaStringArray& namespaceArray);

private:
    // ���ӺͻỰ����
    UaString        m_applicationName;
    UaString        m_serverUrl;
    UaString        m_discoveryUrl;
    OpcUa_Boolean   m_bAutomaticReconnect;
    OpcUa_Boolean   m_bRetryInitialConnect;

    // NamespaceArray �� NodeIds
    UaStringArray   m_namespaceArray;
    UaNodeIdArray   m_nodesToRead;
    UaNodeIdArray   m_nodesToWrite;
    UaNodeIdArray   m_nodesToMonitor;
    UaVariantArray  m_writeValues;
    UaNodeId        m_eventTypeToFilter;
    UaNodeIdArray   m_methodsToCall;
    UaNodeIdArray   m_objectToCall;

    // ֤��
    UaString        m_certificateTrustListLocation;
    UaString        m_certificateRevocationListLocation;
    UaString        m_issuersCertificatesLocation;
    UaString        m_issuersRevocationListLocation;
    UaString        m_clientCertificateFile;
    UaString        m_clientPrivateKeyFile;
};
