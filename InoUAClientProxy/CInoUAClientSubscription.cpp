#include "CInoUAClientSubscription.h"
#include "uasubscription.h"
#include "uasession.h"
#include "CInoUAClientConfig.h"
#include "InoCommonDef.h"

CInoUAClientSubscription::CInoUAClientSubscription(UaSession* pSession, CInoUAClientConfig* pConfiguration)
    : m_pSession(pSession),
    m_pSubscription(nullptr),
    m_pConfiguration(pConfiguration)
{
}

CInoUAClientSubscription::~CInoUAClientSubscription()
{
    if (nullptr != m_pSubscription)
    {
        deleteSubscription();
    }
}

// 描述：订阅的状态发生变化，客户端回调函数
// 时间：2021-10-20
// 备注：无
void CInoUAClientSubscription::subscriptionStatusChanged(
    OpcUa_UInt32 clientSubscriptionHandle,
    const UaStatus& status)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle);

    if (status.isBad())
    {
        printf("Subscription not longer valid - failed with status %s\n", status.toString().toUtf8());

        // 在服务器上恢复订阅
        UaStatus result = createSubscriptionMonitors(true);
        printf("-------------------------------------------------------------\n");
        if (result.isGood())
        {
            printf("RecoverSubscription succeeded.\n");
        }
        else
        {
            printf("RecoverSubscription failed with status %s\n", result.toString().toUtf8());
        }
        printf("-------------------------------------------------------------\n");
    }
}

// 描述：监视项数据更改，另：删除监控项、关闭采样或禁用发布后，数据更改也可能到达
// 时间：2021-10-20
// 备注：无
void CInoUAClientSubscription::dataChange(
    OpcUa_UInt32 clientSubscriptionHandle,
    const UaDataNotifications& dataNotifications,
    const UaDiagnosticInfos& diagnosticInfos)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle);
    OpcUa_ReferenceParameter(diagnosticInfos);

    printf("-- DataChange Notification ---------------------------------\n");
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
    printf("------------------------------------------------------------\n");
}

// 描述：订阅事件通知
// 时间：2021-10-20
// 备注：无
void CInoUAClientSubscription::newEvents(
    OpcUa_UInt32 clientSubscriptionHandle,
    UaEventFieldLists& eventFieldList)
{
    OpcUa_UInt32 i = 0;
    printf("-- Event newEvents -----------------------------------------\n");
    printf("clientSubscriptionHandle %d \n", clientSubscriptionHandle);
    for (i = 0; i < eventFieldList.length(); i++)
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
    printf("------------------------------------------------------------\n");
}

// 描述：在服务器上创建订阅
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClientSubscription::createSubscription()
{
    if (nullptr != m_pSubscription)
    {
        printf("\nError: Subscription already created\n");
        return OpcUa_BadInvalidState;
    }

    ServiceSettings serviceSettings;

    SubscriptionSettings subscriptionSettings;
    subscriptionSettings.publishingInterval = 100;

    printf("\nCreating subscription ...\n");
    UaStatus result = m_pSession->createSubscription(
        serviceSettings,
        this,
        1,
        subscriptionSettings,
        OpcUa_True,
        &m_pSubscription);

    if (result.isGood())
    {
        printf("CreateSubscription succeeded\n");
    }
    else
    {
        m_pSubscription = nullptr;
        printf("CreateSubscription failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

// 描述：在服务器上删除订阅
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClientSubscription::deleteSubscription()
{
    if (m_pSubscription == nullptr)
    {
        printf("\nError: No Subscription created\n");
        return OpcUa_BadInvalidState;
    }

    UaStatus result;
    ServiceSettings serviceSettings;

    // 让 SDK 清理现有订阅的资源
    printf("\nDeleting subscription ...\n");
    result = m_pSession->deleteSubscription(
        serviceSettings,
        &m_pSubscription);

    if (result.isGood())
    {
        printf("DeleteSubscription succeeded\n");
    }
    else
    {
        printf("DeleteSubscription failed with status %s\n", result.toString().toUtf8());
    }

    m_pSubscription = nullptr;

    return result;
}

// 描述：在订阅中创建受监控的项目
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClientSubscription::createMonitoredItems()
{
#pragma TODO("CInoUAClientSubscription::createMonitoredItems 再看")
    if (m_pSubscription == nullptr)
    {
        printf("\nError: No Subscription created\n");
        return OpcUa_BadInvalidState;
    }

    UaMonitoredItemCreateRequests itemsToCreate;

    // 配置一个事件监控项——这里我们使用服务器对象
    itemsToCreate.create(1);
    itemsToCreate[0].ItemToMonitor.AttributeId = OpcUa_Attributes_EventNotifier;
    itemsToCreate[0].ItemToMonitor.NodeId.Identifier.Numeric = OpcUaId_Server;
    itemsToCreate[0].RequestedParameters.ClientHandle = 0;
    itemsToCreate[0].RequestedParameters.SamplingInterval = 0;
    itemsToCreate[0].RequestedParameters.QueueSize = 0;
    itemsToCreate[0].RequestedParameters.DiscardOldest = OpcUa_True;
    itemsToCreate[0].MonitoringMode = OpcUa_MonitoringMode_Reporting;

    // 定义与每个事件一起发送的事件字段
    UaEventFilter eventFilter;
    UaSimpleAttributeOperand selectElement;
    selectElement.setBrowsePathElement(0, UaQualifiedName("Message", 0), 1);
    eventFilter.setSelectClauseElement(0, selectElement, 3);
    selectElement.setBrowsePathElement(0, UaQualifiedName("SourceName", 0), 1);
    eventFilter.setSelectClauseElement(1, selectElement, 3);
    selectElement.setBrowsePathElement(0, UaQualifiedName("Severity", 0), 1);
    eventFilter.setSelectClauseElement(2, selectElement, 3);

    // 接收 ControllerEventType 类型的事件
    UaContentFilterElement* pContentFilterElement = new UaContentFilterElement;

    // OfType操作符
    pContentFilterElement->setFilterOperator(OpcUa_FilterOperator_OfType);

    // 1 (Literal)操作符
    UaFilterOperand* pOperand = new UaLiteralOperand;
    ((UaLiteralOperand*)pOperand)->setLiteralValue(m_pConfiguration->getEventTypeToFilter());
    pContentFilterElement->setFilterOperand(0, pOperand, 1);

    UaContentFilter* pContentFilter = new UaContentFilter;
    pContentFilter->setContentFilterElement(0, pContentFilterElement, 1);
    eventFilter.setWhereClause(pContentFilter);

    // 为监控项目设置过滤器
    eventFilter.detachFilter(itemsToCreate[0].RequestedParameters.Filter);

    ServiceSettings serviceSettings;
    UaMonitoredItemCreateResults createResults;
    printf("\nAdding monitored items to subscription ...\n");
    UaStatus result = m_pSubscription->createMonitoredItems(
        serviceSettings,
        OpcUa_TimestampsToReturn_Both,
        itemsToCreate,
        createResults);

    // 调用失败
    if (result.isNotGood())
    {
        printf("CreateMonitoredItems failed with status %s\n", result.toString().toUtf8());
        return result;
    }

    // 调用成功，检查结果
    for (OpcUa_UInt32 i = 0; i < createResults.length(); i++)
    {
        if (OpcUa_IsGood(createResults[i].StatusCode))
        {
            printf("CreateMonitoredItems succeeded for item: %s\n",
                UaNodeId(itemsToCreate[i].ItemToMonitor.NodeId).toXmlString().toUtf8());
        }
        else
        {
            printf("CreateMonitoredItems failed for item: %s - Status %s\n",
                UaNodeId(itemsToCreate[i].ItemToMonitor.NodeId).toXmlString().toUtf8(),
                UaStatus(createResults[i].StatusCode).toString().toUtf8());
        }
    }

    return result;
}

// 描述：设置客户端代理配置
// 时间：2021-10-20
// 备注：无
void CInoUAClientSubscription::setConfiguration(CInoUAClientConfig* pConfiguration)
{
    m_pConfiguration = pConfiguration;
}

// 描述：在服务器上创建订阅、监视项
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClientSubscription::createSubscriptionMonitors(bool bDeleteSubscription/* = false*/)
{
    UaStatus result;

    // 删除现有订阅
    if (bDeleteSubscription && nullptr != m_pSubscription)
    {
        deleteSubscription();
    }

    // 创建新订阅
    result = createSubscription();

    // 创建监控项
    if (result.isGood())
    {
        result = createMonitoredItems();
    }

    return result;
}
