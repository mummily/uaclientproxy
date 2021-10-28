#pragma once

#include "uabase.h"
#include "uaclientsdk.h"

using namespace UaClientSdk;

class CInoUASubscription;
class CInoUASubscriptionCallback : public UaSubscriptionCallback
{
    UA_DISABLE_COPY(CInoUASubscriptionCallback);
public:
    CInoUASubscriptionCallback(CInoUASubscription* pSubscription);
    virtual ~CInoUASubscriptionCallback();

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

private:
    CInoUASubscription* m_pSubscription = nullptr;
};
