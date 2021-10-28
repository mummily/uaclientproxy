#pragma once
#include "uabase.h"
#include "uaclientsdk.h"

class UaStatus;
class UaSession;
class UaSubscription;
class CInoUAClientConfig;
class CInoUASubscriptionCallback;

using namespace UaClientSdk;

class CInoUASubscription
{
    UA_DISABLE_COPY(CInoUASubscription);
public:
    CInoUASubscription(UaClientSdk::UaSession* pSession, CInoUAClientConfig* pConfiguration);
    virtual ~CInoUASubscription();

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
    UaClientSdk::UaSession* m_pSession = nullptr;                // 当前会话
    UaClientSdk::UaSubscription* m_pSubscription = nullptr;      // 当前订阅
    CInoUASubscriptionCallback* m_pSubscriptionCallback = nullptr; // 订阅回调
    CInoUAClientConfig* m_pConfiguration = nullptr; // 当前客户端配置
};

