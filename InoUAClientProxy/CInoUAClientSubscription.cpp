#include "CInoUAClientSubscription.h"
#include "uasubscription.h"
#include "uasession.h"
#include "CInoUAClientConfig.h"

CInoUAClientSubscription::CInoUAClientSubscription(CInoUAClientConfig* pConfiguration)
    : m_pSession(nullptr),
    m_pSubscription(nullptr),
    m_pConfiguration(pConfiguration)
{
}

CInoUAClientSubscription::~CInoUAClientSubscription()
{
    if (m_pSubscription)
    {
        deleteSubscription();
    }
}

void CInoUAClientSubscription::subscriptionStatusChanged(
    OpcUa_UInt32      clientSubscriptionHandle,
    const UaStatus& status)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle);

    if (status.isBad())
    {
        printf("Subscription not longer valid - failed with status %s\n", status.toString().toUtf8());

        // �ڷ������ϻָ�����
        recoverSubscription();
    }
}

void CInoUAClientSubscription::dataChange(
    OpcUa_UInt32               clientSubscriptionHandle,
    const UaDataNotifications& dataNotifications,
    const UaDiagnosticInfos& diagnosticInfos)
{
    OpcUa_ReferenceParameter(clientSubscriptionHandle);
    OpcUa_ReferenceParameter(diagnosticInfos);
    OpcUa_UInt32 i = 0;

    printf("-- DataChange Notification ---------------------------------\n");
    for (i = 0; i < dataNotifications.length(); i++)
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

void CInoUAClientSubscription::newEvents(
    OpcUa_UInt32                clientSubscriptionHandle,
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

UaStatus CInoUAClientSubscription::createSubscription(UaSession* pSession)
{
    if (m_pSubscription)
    {
        printf("\nError: Subscription already created\n");
        return OpcUa_BadInvalidState;
    }

    m_pSession = pSession;

    UaStatus result;

    ServiceSettings serviceSettings;
    SubscriptionSettings subscriptionSettings;
    subscriptionSettings.publishingInterval = 100;

    printf("\nCreating subscription ...\n");
    result = pSession->createSubscription(
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

UaStatus CInoUAClientSubscription::deleteSubscription()
{
    if (m_pSubscription == nullptr)
    {
        printf("\nError: No Subscription created\n");
        return OpcUa_BadInvalidState;
    }

    UaStatus result;
    ServiceSettings serviceSettings;

    // �� SDK �������ж��ĵ���Դ
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

UaStatus CInoUAClientSubscription::createMonitoredItems()
{
    if (m_pSubscription == nullptr)
    {
        printf("\nError: No Subscription created\n");
        return OpcUa_BadInvalidState;
    }

    UaStatus result;
    OpcUa_UInt32 i;
    ServiceSettings serviceSettings;
    UaMonitoredItemCreateRequests itemsToCreate;
    UaMonitoredItemCreateResults createResults;

    // ����һ���¼���������������ʹ�÷���������
    itemsToCreate.create(1);

    UaEventFilter            eventFilter;
    UaSimpleAttributeOperand selectElement;
    UaContentFilter* pContentFilter = nullptr;
    UaContentFilterElement* pContentFilterElement = nullptr;
    UaFilterOperand* pOperand = nullptr;

    itemsToCreate[0].ItemToMonitor.AttributeId = OpcUa_Attributes_EventNotifier;
    itemsToCreate[0].ItemToMonitor.NodeId.Identifier.Numeric = OpcUaId_Server;
    itemsToCreate[0].RequestedParameters.ClientHandle = 0;
    itemsToCreate[0].RequestedParameters.SamplingInterval = 0;
    itemsToCreate[0].RequestedParameters.QueueSize = 0;
    itemsToCreate[0].RequestedParameters.DiscardOldest = OpcUa_True;
    itemsToCreate[0].MonitoringMode = OpcUa_MonitoringMode_Reporting;

    // ������ÿ���¼�һ���͵��¼��ֶ�
    selectElement.setBrowsePathElement(0, UaQualifiedName("Message", 0), 1);
    eventFilter.setSelectClauseElement(0, selectElement, 3);
    selectElement.setBrowsePathElement(0, UaQualifiedName("SourceName", 0), 1);
    eventFilter.setSelectClauseElement(1, selectElement, 3);
    selectElement.setBrowsePathElement(0, UaQualifiedName("Severity", 0), 1);
    eventFilter.setSelectClauseElement(2, selectElement, 3);

    // ���� ControllerEventType ���͵��¼�
    pContentFilter = new UaContentFilter;
    pContentFilterElement = new UaContentFilterElement;

    // OfType������
    pContentFilterElement->setFilterOperator(OpcUa_FilterOperator_OfType);

    // 1 (Literal)������
    pOperand = new UaLiteralOperand;
    ((UaLiteralOperand*)pOperand)->setLiteralValue(m_pConfiguration->getEventTypeToFilter());
    pContentFilterElement->setFilterOperand(0, pOperand, 1);
    pContentFilter->setContentFilterElement(0, pContentFilterElement, 1);
    eventFilter.setWhereClause(pContentFilter);

    // Ϊ�����Ŀ���ù�����
    eventFilter.detachFilter(itemsToCreate[0].RequestedParameters.Filter);

    printf("\nAdding monitored items to subscription ...\n");
    result = m_pSubscription->createMonitoredItems(
        serviceSettings,
        OpcUa_TimestampsToReturn_Both,
        itemsToCreate,
        createResults);

    if (result.isGood())
    {
        // �����
        for (i = 0; i < createResults.length(); i++)
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
    }
    // �������ʧ��
    else
    {
        printf("CreateMonitoredItems failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

void CInoUAClientSubscription::setConfiguration(CInoUAClientConfig* pConfiguration)
{
    m_pConfiguration = pConfiguration;
}

UaStatus CInoUAClientSubscription::recoverSubscription()
{
    UaStatus result;

    // ɾ�����ж���
    if (m_pSubscription)
    {
        deleteSubscription();
    }

    // �����¶���
    result = createSubscription(m_pSession);

    // ���������
    if (result.isGood())
    {
        result = createMonitoredItems();
    }

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

    return result;
}
