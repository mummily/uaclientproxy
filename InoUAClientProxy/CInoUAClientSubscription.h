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

    // ���ĵ�״̬�����仯���ͻ��˻ص�����
    virtual void subscriptionStatusChanged(
        OpcUa_UInt32 clientSubscriptionHandle,
        const UaStatus& status);

    // ���������ݸ��ģ���ɾ�������رղ�������÷��������ݸ���Ҳ���ܵ���
    virtual void dataChange(
        OpcUa_UInt32 clientSubscriptionHandle,
        const UaDataNotifications& dataNotifications,
        const UaDiagnosticInfos& diagnosticInfos);

    // �����¼�֪ͨ
    virtual void newEvents(
        OpcUa_UInt32 clientSubscriptionHandle,
        UaEventFieldLists& eventFieldList);

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
    UaSession* m_pSession = nullptr;                // ��ǰ�Ự
    UaSubscription* m_pSubscription = nullptr;      // ��ǰ����
    CInoUAClientConfig* m_pConfiguration = nullptr; // ��ǰ�ͻ�������
};
