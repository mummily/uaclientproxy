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

    // �ڷ������ϴ������ġ�������
    UaStatus createSubscriptionMonitors(bool bDeleteSubscription = false);
    // �ڷ�������ɾ������
    UaStatus deleteSubscription();
    // ����Ҫ��ص� NodeId �б������
    void setConfiguration(CInoSessionConfig* pConfiguration);

private:
    // �ڷ������ϴ�������
    UaStatus createSubscription();
    // �ڶ����д����ܼ�ص���Ŀ
    UaStatus createMonitoredItems();

private:
    UaClientSdk::UaSession* m_pSession = nullptr;                // ��ǰ�Ự
    UaClientSdk::UaSubscription* m_pSubscription = nullptr;      // ��ǰ����
    CInoSubscriptionCallback* m_pSubscriptionCallback = nullptr; // ���Ļص�
    CInoSessionConfig* m_pConfiguration = nullptr; // ��ǰ�ͻ�������
};

