#include "InoSubscriptionCallback.h"
#include "uasubscription.h"
#include "uasession.h"
#include "InoSessionConfig.h"
#include "InoCommonDef.h"
#include "ScopeExit.h"
#include "InoSession.h"

InoSubscriptionCallback::InoSubscriptionCallback(InoSession* pInoSession)
    : m_pSession(pInoSession)
{
}

InoSubscriptionCallback::~InoSubscriptionCallback()
{
}

// 描述：订阅的状态发生变化，客户端回调函数
// 时间：2021-10-20
// 备注：无
void InoSubscriptionCallback::subscriptionStatusChanged(
    OpcUa_UInt32 clientSubscriptionHandle,
    const UaStatus& status)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle);

    if (status.isBad())
    {
        printf("Subscription not longer valid - failed with status %s\n", status.toString().toUtf8());

        // 在服务器上恢复订阅
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

// 描述：监视项数据更改，另：删除监控项、关闭采样或禁用发布后，数据更改也可能到达
// 时间：2021-10-20
// 备注：无
void InoSubscriptionCallback::dataChange(
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

// 描述：订阅事件通知
// 时间：2021-10-20
// 备注：无
void InoSubscriptionCallback::newEvents(
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
