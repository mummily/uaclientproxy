#include "CInoSubscriptionCallback.h"
#include "uasubscription.h"
#include "uasession.h"
#include "CInoSessionConfig.h"
#include "InoCommonDef.h"
#include "ScopeExit.h"
#include "CInoSession.h"

CInoSubscriptionCallback::CInoSubscriptionCallback(CInoSession* pInoSession)
    : m_pSession(pInoSession)
{
}

CInoSubscriptionCallback::~CInoSubscriptionCallback()
{
}

// ���������ĵ�״̬�����仯���ͻ��˻ص�����
// ʱ�䣺2021-10-20
// ��ע����
void CInoSubscriptionCallback::subscriptionStatusChanged(
    OpcUa_UInt32 clientSubscriptionHandle,
    const UaStatus& status)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle);

    if (status.isBad())
    {
        printf("Subscription not longer valid - failed with status %s\n", status.toString().toUtf8());

        // �ڷ������ϻָ�����
        UaStatus result = m_pSession->createSubscriptionMonitors(true);
        printf("-------------------------------------------------------------\n");
        SCOPE_EXIT(
            printf("-------------------------------------------------------------\n");
        );

        if (result.isGood())
        {
            printf("RecoverSubscription succeeded.\n");
        }
        else
        {
            printf("RecoverSubscription failed with status %s\n", result.toString().toUtf8());
        }
    }
}

// ���������������ݸ��ģ�����ɾ�������رղ�������÷��������ݸ���Ҳ���ܵ���
// ʱ�䣺2021-10-20
// ��ע����
void CInoSubscriptionCallback::dataChange(
    OpcUa_UInt32 clientSubscriptionHandle,
    const UaDataNotifications& dataNotifications,
    const UaDiagnosticInfos& diagnosticInfos)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle);
    OpcUa_ReferenceParameter(diagnosticInfos);

    printf("-- DataChange Notification ---------------------------------\n");
    SCOPE_EXIT(
        printf("------------------------------------------------------------\n");
    );

    for (OpcUa_UInt32 i = 0; i < dataNotifications.length(); i++)
    {
        if (OpcUa_IsGood(dataNotifications[i].Value.StatusCode))
        {
            UaVariant tempValue = dataNotifications[i].Value.Value;
            printf("  Variable = %d value = %s\n", dataNotifications[i].ClientHandle, tempValue.toString().toUtf8());
        }
        else
        {
            UaStatus itemError(dataNotifications[i].Value.StatusCode);
            printf("  Variable = %d failed with status %s\n", dataNotifications[i].ClientHandle, itemError.toString().toUtf8());
        }
    }
}

// �����������¼�֪ͨ
// ʱ�䣺2021-10-20
// ��ע����
void CInoSubscriptionCallback::newEvents(
    OpcUa_UInt32 clientSubscriptionHandle,
    UaEventFieldLists& eventFieldList)
{
    printf("-- Event newEvents -----------------------------------------\n");
    SCOPE_EXIT(
        printf("------------------------------------------------------------\n");
    );

    printf("clientSubscriptionHandle %d \n", clientSubscriptionHandle);
    for (OpcUa_UInt32 i = 0; i < eventFieldList.length(); i++)
    {
        UaVariant message = eventFieldList[i].EventFields[0];
        UaVariant sourceName = eventFieldList[i].EventFields[1];
        UaVariant severity = eventFieldList[i].EventFields[2];
        printf("Event[%d] Message = %s SourceName = %s Severity = %s\n",
            i,
            message.toString().toUtf8(),
            sourceName.toString().toUtf8(),
            severity.toString().toUtf8());
    }
}