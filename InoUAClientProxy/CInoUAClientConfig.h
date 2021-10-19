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

    // 获取连接和会话参数
    UaString getServerUrl() const;
    UaString getDiscoveryUrl() const;
    UaString getApplicationName() const;
    UaString getProductUri() const;
    OpcUa_Boolean getAutomaticReconnect() const;
    OpcUa_Boolean getRetryInitialConnect() const;

    // 获取 NodeId 和值的列表
    UaNodeIdArray getNodesToRead() const;
    UaNodeIdArray getNodesToWrite() const;
    UaNodeIdArray getNodesToMonitor() const;
    UaVariantArray getWriteValues() const;
    UaNodeId getEventTypeToFilter() const;
    UaNodeIdArray getMethodsToCall() const;
    UaNodeIdArray getObjectsToCall() const;

    // 从文件加载配置以填充连接参数、NamespaceArray 和 NodeIds
    UaStatus loadConfiguration(const UaString& sConfigurationFile);

    // 创建文件夹结构来处理证书并加载或创建客户端证书。
    UaStatus setupSecurity(SessionSecurityInfo& sessionSecurityInfo);

    // 更新所有 nodeId 的命名空间索引并更新内部 namespaceArray
    UaStatus updateNamespaceIndexes(const UaStringArray& namespaceArray);

private:
    // 连接和会话配置
    UaString        m_applicationName;
    UaString        m_serverUrl;
    UaString        m_discoveryUrl;
    OpcUa_Boolean   m_bAutomaticReconnect;
    OpcUa_Boolean   m_bRetryInitialConnect;

    // NamespaceArray 和 NodeIds
    UaStringArray   m_namespaceArray;
    UaNodeIdArray   m_nodesToRead;
    UaNodeIdArray   m_nodesToWrite;
    UaNodeIdArray   m_nodesToMonitor;
    UaVariantArray  m_writeValues;
    UaNodeId        m_eventTypeToFilter;
    UaNodeIdArray   m_methodsToCall;
    UaNodeIdArray   m_objectToCall;

    // 证书
    UaString        m_certificateTrustListLocation;
    UaString        m_certificateRevocationListLocation;
    UaString        m_issuersCertificatesLocation;
    UaString        m_issuersRevocationListLocation;
    UaString        m_clientCertificateFile;
    UaString        m_clientPrivateKeyFile;
};
