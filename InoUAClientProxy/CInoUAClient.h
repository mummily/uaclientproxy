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

    // 连接状态变更回调函数
    virtual void connectionStatusChanged(OpcUa_UInt32 clientConnectionId, UaClient::ServerStatus serverStatus);
    // 设置客户端配置信息
    void setConfiguration(CInoUAClientConfig* pConfiguration);
    // 客户端是否处于连接状态
    OpcUa_Boolean isConnected() const;
    // 查找服务器并输出服务器信息
    UaStatus discover();
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
    UaStatus read();
    // 根据配置文件，节点进行写值
    UaStatus write();
    // 给注册的节点写入值
    UaStatus writeRegistered();
    // 在服务器上创建订阅和监视项
    UaStatus subscribe();
    // 在服务器上退订
    UaStatus unsubscribe();
    // 注册节点，默认注册所有要写入的节点
    UaStatus registerNodes();
    // 注销节点
    UaStatus unregisterNodes();
    // 回调对象的方法，方法无参数
    UaStatus callMethods();

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
    // 回调对象objectNodeId的methodNodeId方法，方法无参数
    UaStatus callMethodInternal(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId);
    // 输出浏览结果referenceDescriptions
    void printBrowseResults(const UaReferenceDescriptions& referenceDescriptions);
    // 输出证书信息
    void printCertificateData(const UaByteString& serverCertificate);
    // 判断用户接受证书状态
    int userAcceptCertificate();

private:
    UaSession* m_pSession = nullptr;                        // 会话
    CInoUAClientSubscription* m_pSubscription = nullptr;    // 订阅
    CInoUAClientConfig* m_pConfiguration = nullptr;         // 客户端配置
    UaClient::ServerStatus m_serverStatus;                  // 客户端连接服务器状态：连接或重连
    UaNodeIdArray m_registeredNodes;                        // 注册的节点：默认是所有要写入的节点
};

