#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

using namespace UaClientSdk;

class Configuration;

class SampleSubscription :
    public UaSubscriptionCallback
{
    UA_DISABLE_COPY(SampleSubscription);
public:
    SampleSubscription(Configuration* pConfiguration);
    virtual ~SampleSubscription();

    // 回调
    virtual void subscriptionStatusChanged(
        OpcUa_UInt32    clientSubscriptionHandle,
        const UaStatus& status);
    virtual void dataChange(
        OpcUa_UInt32               clientSubscriptionHandle,
        const UaDataNotifications& dataNotifications,
        const UaDiagnosticInfos& diagnosticInfos);
    virtual void newEvents(
        OpcUa_UInt32                clientSubscriptionHandle,
        UaEventFieldLists& eventFieldList);

    // 在服务器上创建/删除订阅
    UaStatus createSubscription(UaSession* pSession);
    UaStatus deleteSubscription();

    // 在订阅中创建受监控的项目
    UaStatus createMonitoredItems();

    // 设置要监控的 NodeId 列表的配置
    void setConfiguration(Configuration* pConfiguration);

private:
    UaStatus recoverSubscription();

private:
    UaSession* m_pSession;
    UaSubscription* m_pSubscription;
    Configuration* m_pConfiguration;
};
