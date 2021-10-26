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

    // 加载客户端连接配置
    UaStatus loadConfiguration(const UaString& sConfigurationFile);

    // 创建文件夹结构来处理证书并加载或创建客户端证书。
    UaStatus setupSecurity(SessionSecurityInfo& sessionSecurityInfo);

    // 更新所有 nodeId 的命名空间索引并更新内部 namespaceArray
    UaStatus updateNamespaceIndexes(const UaStringArray& namespaceArray);

private:
    // 连接和会话配置
    UaString        m_applicationName;      // 应用名称
    UaString        m_serverUrl;            // 服务Url
    UaString        m_discoveryUrl;         // 查找Url
    OpcUa_Boolean   m_bAutomaticReconnect;  // 是否自动重连
    OpcUa_Boolean   m_bRetryInitialConnect; // 是否尝试初始化连接

    // NamespaceArray 和 NodeIds
    UaStringArray   m_namespaceArray;       // 命名空间
    UaVariantArray  m_writeValues;          // 写入的变量的值
    UaNodeId        m_eventTypeToFilter;    // 过滤的事件类型

    UaNodeIdArray   m_nodesToRead;          // 读取的变量
    UaNodeIdArray   m_nodesToWrite;         // 写入的变量
    UaNodeIdArray   m_nodesToMonitor;       // 监视的变量
    UaNodeIdArray   m_methodsToCall;        // 方法
    UaNodeIdArray   m_objectToCall;         // 对象

    // 证书
    UaString        m_certificateTrustListLocation;     // 信任的证书
    UaString        m_certificateRevocationListLocation;// 禁止的证书
    UaString        m_issuersCertificatesLocation;      // 发行人证书
    UaString        m_issuersRevocationListLocation;    // 发行人禁止证书
    UaString        m_clientCertificate;                // 客户证书
    UaString        m_clientPrivateKey;                 // 客户私钥
};
