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
    CInoUAClientSubscription(CInoUAClientConfig* pConfiguration);
    virtual ~CInoUAClientSubscription();

    // �ص�
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

    // �ڷ������ϴ���/ɾ������
    UaStatus createSubscription(UaSession* pSession);
    UaStatus deleteSubscription();

    // �ڶ����д����ܼ�ص���Ŀ
    UaStatus createMonitoredItems();

    // ����Ҫ��ص� NodeId �б������
    void setConfiguration(CInoUAClientConfig* pConfiguration);

private:
    UaStatus recoverSubscription();

private:
    UaSession* m_pSession;
    UaSubscription* m_pSubscription;
    CInoUAClientConfig* m_pConfiguration;
};
