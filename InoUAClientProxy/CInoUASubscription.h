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

    // �ڷ������ϴ������ġ�������
    UaStatus createSubscriptionMonitors(bool bDeleteSubscription = false);
    // �ڷ�������ɾ������
    UaStatus deleteSubscription();
    // ����Ҫ��ص� NodeId �б������
    void setConfiguration(CInoUAClientConfig* pConfiguration);

private:
    // �ڷ������ϴ�������
    UaStatus createSubscription();
    // �ڶ����д����ܼ�ص���Ŀ
    UaStatus createMonitoredItems();

private:
    UaClientSdk::UaSession* m_pSession = nullptr;                // ��ǰ�Ự
    UaClientSdk::UaSubscription* m_pSubscription = nullptr;      // ��ǰ����
    CInoUASubscriptionCallback* m_pSubscriptionCallback = nullptr; // ���Ļص�
    CInoUAClientConfig* m_pConfiguration = nullptr; // ��ǰ�ͻ�������
};

