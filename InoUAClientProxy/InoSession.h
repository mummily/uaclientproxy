#pragma once

#include "InoExportDef.h"
#include "uaclientsdk.h"
#include "uasession.h"

using namespace UaClientSdk;

class UaSession;
class CInoSubscription;
class InoSessionConfig;
class InoRedSession;
class InoSessionCallback;
class InoSubscriptionCallback;
class INO_EXPORT InoSession : public UaClientSdk::UaSession
{
    UA_DISABLE_COPY(InoSession);

public:
    InoSession();
    virtual ~InoSession();

    friend class CInoRedSession;

    // 设置客户端配置信息
    void setConfiguration(InoSessionConfig* pConfiguration);
    // 查找服务器并输出服务器信息
    UaStatus discover(const UaString& sDiscoveryUrl);
    // 非安连接服务器
    UaStatus connect();
    // 安全连接服务器
    UaStatus connectSecure();
    // 断开连接
    UaStatus disconnect();
    // 从根节点浏览节点
    UaStatus browseSimple();
    // 继续浏览
    UaStatus browseContinuationPoint();
    // 根据配置文件，节点进行读值
    UaStatus read(const UaNodeIdArray& nodes);
    // 根据配置文件，节点进行写值
    UaStatus write(const UaNodeIdArray& nodes, const UaVariantArray& values);
    // 给注册的节点写入值
    UaStatus writeRegistered(const UaVariantArray& values);
    // 在服务器上创建订阅和监视项
    UaStatus subscribe();
    UaStatus createSubscriptionMonitors(bool bDeleteSubscription = false);
    // 在服务器上退订
    UaStatus unsubscribe();
    // 注册节点，默认注册所有要写入的节点
    UaStatus reRegisterNodes();
    UaStatus registerNodes(const UaNodeIdArray& nodesToRegister);
    // 注销节点
    UaStatus unregisterNodes();

    // 回调对象的方法
    using UaStatusArray = UaObjectArray<UaStatus>;
    UaStatus callMethodList(
        const UaNodeIdArray& objectNodeIds,
        const UaNodeIdArray& methodNodeIds,
        UaStatusArray& results);
    UaStatus callMethod(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId);

    // 更新所有 nodeId 的命名空间索引并更新内部 namespaceArray
    UaStatus updateNamespaceIndexes();

private:
    // 从节点nodeToBrowse浏览地址空间
    UaStatus browseInternal(const UaNodeId& nodeToBrowse, OpcUa_UInt32 maxReferencesToReturn);
    // 连接服务器，sessionConnectInfo读自配置，使用sessionSecurityInfo连接服务器serverUrl
    UaStatus connectInternal(const UaString& serverUrl, SessionSecurityInfo& sessionSecurityInfo);
    // 往节点nodesToWrite中写入valuesToWrite值
    UaStatus writeInternal(const UaNodeIdArray& nodesToWrite, const UaVariantArray& valuesToWrite);
    // 在服务器上查找安全端点
    UaStatus findSecureEndpoint(SessionSecurityInfo& sessionSecurityInfo);
    // 验证服务器证书
    UaStatus checkServerCertificateTrust(SessionSecurityInfo& sessionSecurityInfo);
    // 输出浏览结果referenceDescriptions
    void printBrowseResults(const UaReferenceDescriptions& referenceDescriptions);
    // 输出证书信息
    void printCertificateData(const UaByteString& serverCertificate);
    // 判断用户接受证书状态
    int userAcceptCertificate();
    // 在服务器上删除订阅
    UaStatus deleteSubscription();
    // 在服务器上创建订阅
    UaStatus createSubscription();
    // 在订阅中创建受监控的项目
    UaStatus createMonitoredItems(const UaNodeId& eventTypeToFilter);

private:
    InoSessionCallback*            m_pSessionCallback = nullptr;  // 会话回调
    UaClientSdk::UaSubscription*    m_pSubscription = nullptr;     // 订阅
    InoSubscriptionCallback*       m_pSubscriptionCallback = nullptr; // 订阅回调
    InoSessionConfig*              m_pSessionConfig = nullptr;     // 客户端配置
    UaNodeIdArray                   m_registeredNodes;              // 注册的节点：默认是所有要写入的节点
};

