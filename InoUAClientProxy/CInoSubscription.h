#pragma once
#include "uabase.h"
#include "uaclientsdk.h"

class UaStatus;
class UaSession;
class UaSubscription;
class CInoSessionConfig;
class CInoSubscriptionCallback;

using namespace UaClientSdk;

class CInoSubscription
{
    UA_DISABLE_COPY(CInoSubscription);
public:
    CInoSubscription(UaClientSdk::UaSession* pSession, CInoSessionConfig* pConfiguration);
    virtual ~CInoSubscription();

    // 在服务器上创建订阅、监视项
    UaStatus createSubscriptionMonitors(bool bDeleteSubscription = false);
    // 在服务器上删除订阅
    UaStatus deleteSubscription();
    // 设置要监控的 NodeId 列表的配置
    void setConfiguration(CInoSessionConfig* pConfiguration);

private:
    // 在服务器上创建订阅
    UaStatus createSubscription();
    // 在订阅中创建受监控的项目
    UaStatus createMonitoredItems();

private:
    UaClientSdk::UaSession* m_pSession = nullptr;                // 当前会话
    UaClientSdk::UaSubscription* m_pSubscription = nullptr;      // 当前订阅
    CInoSubscriptionCallback* m_pSubscriptionCallback = nullptr; // 订阅回调
    CInoSessionConfig* m_pConfiguration = nullptr; // 当前客户端配置
};

