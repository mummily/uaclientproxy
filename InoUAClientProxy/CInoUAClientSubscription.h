#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

using namespace UaClientSdk;

class CInoUAClientConfig;

class CInoUAClientSubscription :
    public UaSubscriptionCallback
{
    UA_DISABLE_COPY(CInoUAClientSubscription);
public:
    CInoUAClientSubscription(UaSession* pSession, CInoUAClientConfig* pConfiguration);
    virtual ~CInoUAClientSubscription();

    // 订阅的状态发生变化，客户端回调函数
    virtual void subscriptionStatusChanged(
        OpcUa_UInt32 clientSubscriptionHandle,
        const UaStatus& status);

    // 监视项数据更改，另：删除监控项、关闭采样或禁用发布后，数据更改也可能到达
    virtual void dataChange(
        OpcUa_UInt32 clientSubscriptionHandle,
        const UaDataNotifications& dataNotifications,
        const UaDiagnosticInfos& diagnosticInfos);

    // 订阅事件通知
    virtual void newEvents(
        OpcUa_UInt32 clientSubscriptionHandle,
        UaEventFieldLists& eventFieldList);

    // 在服务器上创建订阅、监视项
    UaStatus createSubscriptionMonitors(bool bDeleteSubscription = false);
    // 在服务器上删除订阅
    UaStatus deleteSubscription();
    // 设置要监控的 NodeId 列表的配置
    void setConfiguration(CInoUAClientConfig* pConfiguration);

private:
    // 在服务器上创建订阅
    UaStatus createSubscription();
    // 在订阅中创建受监控的项目
    UaStatus createMonitoredItems();

private:
    UaSession* m_pSession = nullptr;                // 当前会话
    UaSubscription* m_pSubscription = nullptr;      // 当前订阅
    CInoUAClientConfig* m_pConfiguration = nullptr; // 当前客户端配置
};
