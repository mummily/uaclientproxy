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

private:
    CInoUASubscription* m_pSubscription = nullptr;
};
