#include "CInoUAClient.h"
#include "uasession.h"
#include "CInoUASubscriptionCallback.h"
#include "CInoUAClientConfig.h"
#include "uadiscovery.h"
#include "uapkicertificate.h"
#include "uaplatformdefs.h"
#include "InoCommonDef.h"
#include "uadir.h"
#include "ScopeExit.h"
#include "CInoUASessionCallback.h"

CInoUAClient::CInoUAClient()
{
    m_pSession = new UaSession();
    m_pSessionCallback = new CInoUASessionCallback(this);
    m_pSubscriptionCallback = new CInoUASubscriptionCallback(m_pSession, m_pConfiguration);
}

CInoUAClient::~CInoUAClient()
{
    // ɾ�����ض��Ķ���
    DelAndNil(m_pSubscriptionCallback);

    // �Ͽ����ӣ�ɾ���Ự
    if (m_pSession)
    {
        if (m_pSession->isConnected() != OpcUa_False)
        {
            ServiceSettings serviceSettings;
            m_pSession->disconnect(serviceSettings, OpcUa_True);
        }

        DelAndNil(m_pSession);
    }
}

// ���������ÿͻ���������Ϣ
// ʱ�䣺2021-10-20
// ��ע����
void CInoUAClient::setConfiguration(CInoUAClientConfig* pConfiguration)
{
    assert(nullptr != pConfiguration);

    if (m_pConfiguration == pConfiguration)
        return;

    m_pSubscriptionCallback->setConfiguration(pConfiguration);

    DelAndNil(m_pConfiguration);
    m_pConfiguration = pConfiguration;
}

// ���������ҷ������������������Ϣ
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::discover()
{
    // ��ȡ���÷������б�
    printf("\nCall FindServers on Url %s\n", m_pConfiguration->getDiscoveryUrl().toUtf8());

    UaDiscovery discovery;
    ServiceSettings serviceSettings;
    ClientSecurityInfo clientSecurityInfo;
    UaApplicationDescriptions applicationDescriptions;
    UaStatus result = discovery.findServers(
        serviceSettings,
        m_pConfiguration->getDiscoveryUrl(),
        clientSecurityInfo,
        applicationDescriptions);

    if (result.isNotGood())
    {
        printf("FindServers failed with status %s\n", result.toString().toUtf8());
        return result;
    }

    printf("\nFindServers succeeded\n");

    // ��ӡ�������б�
    for (OpcUa_UInt32 i = 0; i < applicationDescriptions.length(); i++)
    {
        printf("** Application [%d] **********************************************************\n", i);
        SCOPE_EXIT(
            printf("******************************************************************************\n");
        );

        UaString sTemp = &applicationDescriptions[i].ApplicationUri;
        printf(" ApplicationUri       %s\n", sTemp.toUtf8());
        sTemp = &applicationDescriptions[i].ApplicationName.Text;
        printf(" ApplicationName      %s\n", sTemp.toUtf8());

        for (OpcUa_Int32 k = 0; k < applicationDescriptions[i].NoOfDiscoveryUrls; k++)
        {
            UaString sDiscoveryUrl(applicationDescriptions[i].DiscoveryUrls[k]);
            printf("** DiscoveryUrl [%s] ***********************\n", sDiscoveryUrl.toUtf8());
            SCOPE_EXIT(
                printf("************************************************************************\n");
            );

            // ����ÿ����������ȡ���ö˵���б�
            UaEndpointDescriptions endpointDescriptions;
            result = discovery.getEndpoints(
                serviceSettings,
                sDiscoveryUrl,
                clientSecurityInfo,
                endpointDescriptions);

            if (result.isGood())
            {
                // ��ӡ�˵��б�
                for (OpcUa_UInt32 j = 0; j < endpointDescriptions.length(); j++)
                {
                    printf("** Endpoint[%d] ***********************************************\n", j);
                    SCOPE_EXIT(
                        printf("**************************************************************\n");
                    );

                    sTemp = &endpointDescriptions[j].EndpointUrl;
                    printf(" Endpoint URL     %s\n", sTemp.toUtf8());
                    sTemp = &endpointDescriptions[j].SecurityPolicyUri;
                    printf(" Security Policy  %s\n", sTemp.toUtf8());
                    sTemp = "Invalid";
                    if (endpointDescriptions[j].SecurityMode == OpcUa_MessageSecurityMode_None)
                    {
                        sTemp = "None";
                    }
                    if (endpointDescriptions[j].SecurityMode == OpcUa_MessageSecurityMode_Sign)
                    {
                        sTemp = "Sign";
                    }
                    if (endpointDescriptions[j].SecurityMode == OpcUa_MessageSecurityMode_SignAndEncrypt)
                    {
                        sTemp = "SignAndEncrypt";
                    }
                    printf(" Security Mode    %s\n", sTemp.toUtf8());
                }
            }
            else
            {
                printf("GetEndpoints failed with status %s\n", result.toString().toUtf8());
            }
        }
    }

    return result;
}

// �������ͻ����Ƿ�������״̬
// ʱ�䣺2021-10-20
// ��ע����
OpcUa_Boolean CInoUAClient::isConnected() const
{
    return m_pSession->isConnected();
}

// �������ǰ����ӷ�����
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::connect()
{
    // ��ȫ����δ��ʼ�� - û�а�ȫ����
    SessionSecurityInfo sessionSecurityInfo;
    return connectInternal(m_pConfiguration->getServerUrl(), sessionSecurityInfo);
}

// ��������ȫ���ӷ�����
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::connectSecure()
{
    UaStatus result;
    SessionSecurityInfo sessionSecurityInfo;

    //************************************************
    // ���� 1 - ���ػ򴴽��ͻ���֤��
    //************************************************
    // ���ػ򴴽��ͻ���֤�鰲ȫ������Ҫ�ͻ��˺ͷ������˵�֤��
    // setupSecurity ���ؿͻ���֤�鲢��ʼ��֤��洢
    result = m_pConfiguration->setupSecurity(sessionSecurityInfo);

    //************************************************
    // ���� 2 - �ڷ������ϲ��Ұ�ȫ�˵�
    //************************************************
    // ��ͨ���ڵ�һ��ʹ�÷�����ʱ���
    // ���� ServerCertificate��SecurityPolicyUri �� SecurityMode Ӧ������������Ϣ���� URL��һ��洢���Ա����Ժ������������ 
    if (result.isGood())
    {
        result = findSecureEndpoint(sessionSecurityInfo);
    }

    //************************************************
    // ���� 3 - ��֤������֤��
    //************************************************
    // ��һ��ͨ���ڵ�һ������ʱ�Ǳ���ģ��粽�� 2��
    // ���������֤���������б��У������Ӽ��ɹ� 
    if (result.isGood())
    {
        result = checkServerCertificateTrust(sessionSecurityInfo);
    }

    if (result.isGood())
    {
        result = connectInternal(m_pConfiguration->getServerUrl(), sessionSecurityInfo);

        if (result.isBad())
        {
            printf("********************************************************************************************\n");
            printf("Connect with security failed. Make sure the client certificate is in the servers trust list.\n");
            printf("********************************************************************************************\n");
        }
    }

    return result;
}

// ���������ӷ�������sessionConnectInfo��������
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::connectInternal(const UaString& serverUrl, SessionSecurityInfo& sessionSecurityInfo)
{
    UaStatus result;

    // �ṩ�йؿͻ�����Ϣ
    SessionConnectInfo sessionConnectInfo;
    UaString sNodeName("unknown_host");
    char szHostName[256];
    if (0 == UA_GetHostname(szHostName, 256))
    {
        sNodeName = szHostName;
    }

    // ʹ�������е��������Ự������Ϣ
    sessionConnectInfo.sApplicationName = m_pConfiguration->getApplicationName();
    // ʹ������������Ψһ��Ӧ�ó��� URI
    sessionConnectInfo.sApplicationUri = UaString("urn:%1:%2:%3").arg(sNodeName).arg(COMPANY_NAME).arg(PRODUCT_NAME);
    sessionConnectInfo.sProductUri = UaString("urn:%1:%2").arg(COMPANY_NAME).arg(PRODUCT_NAME);
    sessionConnectInfo.sSessionName = sessionConnectInfo.sApplicationUri;
    sessionConnectInfo.bAutomaticReconnect = m_pConfiguration->getAutomaticReconnect();
    sessionConnectInfo.bRetryInitialConnect = m_pConfiguration->getRetryInitialConnect();

    // ���ӵ�������
    printf("\nConnecting to %s\n", serverUrl.toUtf8());
    result = m_pSession->connect(
        serverUrl,
        sessionConnectInfo,
        sessionSecurityInfo,
        m_pSessionCallback);

    if (result.isGood())
    {
        printf("Connect succeeded\n");
    }
    else
    {
        printf("Connect failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

// �������ڵ�nodesToWrite��д��valuesToWriteֵ
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::writeInternal(const UaNodeIdArray& nodesToWrite, const UaVariantArray& valuesToWrite)
{

    // �������
    if (nodesToWrite.length() < 1
        || valuesToWrite.length() < 1)
    {
        return OpcUa_BadInvalidArgument;
    }

    // ��������д�����нڵ�
    UaWriteValues writeValues;
    writeValues.create(nodesToWrite.length());

    for (OpcUa_UInt32 i = 0; i < writeValues.length(); i++)
    {
        writeValues[i].AttributeId = OpcUa_Attributes_Value;
        OpcUa_NodeId_CopyTo(&nodesToWrite[i], &writeValues[i].NodeId);
        // ����Ҫд���ֵ
        OpcUa_Variant_CopyTo(&valuesToWrite[i], &writeValues[i].Value.Value);
    }

    printf("\nWriting...\n");
    UaStatus            result;
    ServiceSettings     serviceSettings;
    UaStatusCodeArray   results;
    UaDiagnosticInfos   diagnosticInfos;
    result = m_pSession->write(
        serviceSettings,
        writeValues,
        results,
        diagnosticInfos);

    if (result.isGood())
    {
        // д�����ɹ� - ������״̬����
        for (OpcUa_UInt32 i = 0; i < results.length(); i++)
        {
            if (OpcUa_IsGood(results[i]))
            {
                printf("Write succeeded for item[%d]\n", i);
            }
            else
            {
                printf("Write failed for item[%d] with status %s\n", i, UaStatus(results[i]).toString().toUtf8());
            }
        }
    }
    else
    {
        // �������ʧ��
        printf("Write failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

// �������ڷ������ϲ��Ұ�ȫ�˵�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::findSecureEndpoint(SessionSecurityInfo& sessionSecurityInfo)
{
    UaStatus result;
    ServiceSettings serviceSettings;
    ClientSecurityInfo clientSecurityInfo;
    UaEndpointDescriptions endpointDescriptions;
    UaDiscovery discovery;
    OpcUa_UInt32 bestSecurityIndex = 0;
    UaString sTemp;

    printf("\nTry to find secure Endpoint on: %s\n", m_pConfiguration->getServerUrl().toUtf8());
    result = discovery.getEndpoints(
        serviceSettings,
        m_pConfiguration->getServerUrl(),
        clientSecurityInfo,
        endpointDescriptions);

    if (result.isGood())
    {
        OpcUa_Byte securityLevel = 0;
        OpcUa_UInt32 i;

        // ѡ��ȫ����õĶ˵�
        for (i = 0; i < endpointDescriptions.length(); i++)
        {
            if (endpointDescriptions[i].SecurityLevel > securityLevel)
            {
                bestSecurityIndex = i;
                securityLevel = endpointDescriptions[i].SecurityLevel;
            }
        }

        // ����ҵ��Ķ˵��Ƿ��ǰ�ȫ�˵�
        if (endpointDescriptions[bestSecurityIndex].SecurityMode < OpcUa_MessageSecurityMode_Sign)
        {
            printf("No secure endpoint available on server\n");
            result = OpcUa_BadSecurityConfig;
        }
        // ��ӡ�ҵ��İ�ȫ�˵�
        else
        {
            printf("Endpoint with best security found:\n");
            sTemp = &endpointDescriptions[bestSecurityIndex].EndpointUrl;
            printf(" Endpoint URL     %s\n", sTemp.toUtf8());
            sTemp = &endpointDescriptions[bestSecurityIndex].SecurityPolicyUri;
            printf(" Security Policy  %s\n", sTemp.toUtf8());
            sTemp = "Invalid";
            if (endpointDescriptions[bestSecurityIndex].SecurityMode == OpcUa_MessageSecurityMode_None)
            {
                sTemp = "None";
            }
            if (endpointDescriptions[bestSecurityIndex].SecurityMode == OpcUa_MessageSecurityMode_Sign)
            {
                sTemp = "Sign";
            }
            if (endpointDescriptions[bestSecurityIndex].SecurityMode == OpcUa_MessageSecurityMode_SignAndEncrypt)
            {
                sTemp = "SignAndEncrypt";
            }
            printf(" Security Mode    %s\n", sTemp.toUtf8());

            // ��������Ӧ����������ü�������֤��һ��洢
            sessionSecurityInfo.serverCertificate = endpointDescriptions[bestSecurityIndex].ServerCertificate;
            // ���ð�ȫģʽ�Ͱ�ȫ����
            sessionSecurityInfo.sSecurityPolicy = endpointDescriptions[bestSecurityIndex].SecurityPolicyUri;
            sessionSecurityInfo.messageSecurityMode = endpointDescriptions[bestSecurityIndex].SecurityMode;
        }
    }
    else
    {
        printf("GetEndpoints failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

// ��������֤������֤��
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::checkServerCertificateTrust(SessionSecurityInfo& sessionSecurityInfo)
{
    UaStatus result;

    // ������֤������Ҫ���²��裺
    // 1. ��ʾ֤�鲢Ҫ���û�����֤��
    // 2. �û����Ծܾ�����ʱ���ܻ����ý���
    // 3. ����ʱ��������֤�����ø��Ƶ��ͻ��������б�
    if (sessionSecurityInfo.verifyServerCertificate().isBad())
    {
        printf("\n");
        printf("\n");
        printf("-------------------------------------------------------\n");
        printf("- The following certificate is not trusted yet        -\n");
        printf("-------------------------------------------------------\n");
        printCertificateData(sessionSecurityInfo.serverCertificate);
        printf("\n");

        printf("'y' + Enter if you want to trust the certificate temporarily.\n");
        printf("'p' + Enter if you want to trust the certificate permanently an copy the server certificate into the client trust list.\n");
        printf("Enter if you don't want to trust the certificate.\n");

        int accept = userAcceptCertificate();

        if (accept == 1)
        {
            printf("Certificate was acceppted temporarily.\n");
            // �Ѿ���֤�������֤���������ڼ�������֤����ʱ����
            sessionSecurityInfo.doServerCertificateVerify = OpcUa_False;
        }
        else if (accept == 2)
        {
            // ��������֤�鸴�Ƶ��ͻ��������б���
            UaPkiCertificate cert = UaPkiCertificate::fromDER(sessionSecurityInfo.serverCertificate);
            UaString sThumbprint = cert.thumbPrint().toHex();
            result = sessionSecurityInfo.saveServerCertificate(sThumbprint);

            if (result.isGood())
            {
                printf("Certificate was accepted permanently.\n");
            }
            else
            {
                printf("Failed to accept certifcate permanently :%s\n", result.toString().toUtf8());
            }
            // ��֤��洢�������б��� - �����������ڼ���֤֤��
            sessionSecurityInfo.doServerCertificateVerify = OpcUa_True;
        }
        else
        {
            printf("Certificate was rejected by user.\n");
            result = OpcUa_BadCertificateUntrusted;
        }
    }

    return result;
}

// �������Ͽ�����
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::disconnect()
{
    ServiceSettings serviceSettings;

    printf("\nDisconnecting ...\n");
    UaStatus result = m_pSession->disconnect(
        serviceSettings,
        OpcUa_True);

    if (result.isGood())
    {
        printf("Disconnect succeeded\n");
    }
    else
    {
        printf("Disconnect failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

// �������Ӹ��ڵ�����ڵ�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::browseSimple()
{
    // �Ӹ��ļ��������û���������Ʒ���
    UaNodeId nodeToBrowse = UaNodeId(OpcUaId_RootFolder);
    UaStatus result = browseInternal(nodeToBrowse, 0);

    return result;
}

// �������������
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::browseContinuationPoint()
{
    UaNodeId nodeToBrowse = UaNodeId("Demo", 2);
    UaStatus result = browseInternal(nodeToBrowse, 5);
    return result;
}

// ���������������ļ����ڵ���ж�ֵ
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::read()
{
    UaNodeIdArray nodes = m_pConfiguration->getNodesToRead();

    UaReadValueIds nodesToRead;
    nodesToRead.create(nodes.length());

    for (OpcUa_UInt32 i = 0; i < nodes.length(); i++)
    {
        nodesToRead[i].AttributeId = OpcUa_Attributes_Value;
        OpcUa_NodeId_CopyTo(&nodes[i], &nodesToRead[i].NodeId);
    }

    printf("\nReading ...\n");
    ServiceSettings serviceSettings;
    UaDataValues values;
    UaDiagnosticInfos diagnosticInfos;
    UaStatus result = m_pSession->read(
        serviceSettings,
        0,
        OpcUa_TimestampsToReturn_Both,
        nodesToRead,
        values,
        diagnosticInfos);

    if (result.isNotGood())
    {
        // �������ʧ��
        printf("Read failed with status %s\n", result.toString().toUtf8());
        return result;
    }

    // ��ȡ����ɹ� - ������״̬����
    for (OpcUa_UInt32 i = 0; i < nodes.length(); i++)
    {
        if (OpcUa_IsGood(values[i].StatusCode))
        {
            printf("Value[%d]: %s\n", i, UaVariant(values[i].Value).toString().toUtf8());
        }
        else
        {
            printf("Read failed for item[%d] with status %s\n", i, UaStatus(values[i].StatusCode).toString().toUtf8());
        }
    }

    return result;
}

// ���������������ļ����ڵ����дֵ
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::write()
{
    UaStatus result;

    result = writeInternal(
        m_pConfiguration->getNodesToWrite(),
        m_pConfiguration->getWriteValues());

    return result;
}

// ��������ע��Ľڵ�д��ֵ
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::writeRegistered()
{
    UaStatus result;

    result = writeInternal(
        m_registeredNodes,
        m_pConfiguration->getWriteValues());

    return result;
}

// �������ڷ������ϴ������ĺͼ�����
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::subscribe()
{
    UaStatus result;
    result = m_pSubscriptionCallback->createSubscriptionMonitors();
    return result;
}

// �������ڷ��������˶�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::unsubscribe()
{
    return m_pSubscriptionCallback->deleteSubscription();
}

// ������ע��ڵ㣬Ĭ��ע������Ҫд��Ľڵ�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::registerNodes()
{
    // ע������Ҫд��Ľڵ�
    UaNodeIdArray nodesToRegister = m_pConfiguration->getNodesToWrite();

    printf("\nRegisterNodes...\n");
    ServiceSettings serviceSettings;
    UaStatus result = m_pSession->registerNodes(
        serviceSettings,
        nodesToRegister,
        m_registeredNodes);

    if (result.isNotGood())
    {
        // �������ʧ��
        printf("RegisterNodes failed with status %s\n", result.toString().toUtf8());
        return result;
    }

    // ע��ڵ����ɹ�
    printf("RegisterNodes succeeded\n");
    for (OpcUa_UInt32 i = 0; i < nodesToRegister.length(); i++)
    {
        printf("Original NodeId[%d]: %s\tRegistered NodeId[%d]: %s\n", i, UaNodeId(nodesToRegister[i]).toXmlString().toUtf8(), i, UaNodeId(m_registeredNodes[i]).toXmlString().toUtf8());
    }

    return result;
}

// ������ע���ڵ�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::unregisterNodes()
{
    ServiceSettings serviceSettings;

    // ע������֮ǰע������нڵ�
    printf("\nUnregisterNodes...\n");
    UaStatus result = m_pSession->unregisterNodes(
        serviceSettings,
        m_registeredNodes);

    if (result.isGood())
    {
        // ע��ڵ����ɹ�
        printf("UnregisterNodes succeeded\n");
    }
    else
    {
        // �������ʧ��
        printf("UnregisterNodes failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

// �������ص�����ķ����������޲���
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::callMethods()
{
    UaStatus result;

    // �������е������з���
    UaNodeIdArray objectNodeIds = m_pConfiguration->getObjectsToCall();
    UaNodeIdArray methodNodeIds = m_pConfiguration->getMethodsToCall();

    for (OpcUa_UInt32 i = 0; i < methodNodeIds.length(); i++)
    {
        UaStatus stat = callMethodInternal(objectNodeIds[i], methodNodeIds[i]);
        if (stat.isNotGood())
        {
            result = stat;
        }
    }

    return result;
}

// ������TODO
// ʱ�䣺2021-10-27
// ��ע����
UaStatus CInoUAClient::updateNamespaceIndexes()
{
    return m_pConfiguration->updateNamespaceIndexes(m_pSession->getNamespaceTable());
}

// �������ӽڵ�nodeToBrowse�����ַ�ռ�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::browseInternal(const UaNodeId& nodeToBrowse, OpcUa_UInt32 maxReferencesToReturn)
{
    // ����browseContext
    BrowseContext browseContext;
    browseContext.browseDirection = OpcUa_BrowseDirection_Forward;
    browseContext.referenceTypeId = OpcUaId_HierarchicalReferences;
    browseContext.includeSubtype = OpcUa_True;
    browseContext.maxReferencesToReturn = maxReferencesToReturn;

    printf("\nBrowsing from Node %s...\n", nodeToBrowse.toXmlString().toUtf8());
    ServiceSettings serviceSettings;
    UaByteString continuationPoint;
    UaReferenceDescriptions referenceDescriptions;
    UaStatus result = m_pSession->browse(
        serviceSettings,
        nodeToBrowse,
        browseContext,
        continuationPoint,
        referenceDescriptions);

    if (result.isNotGood())
    {
        // �������ʧ��
        printf("Browse failed with status %s\n", result.toString().toUtf8());
        return result;
    }

    // ��ӡ���
    printBrowseResults(referenceDescriptions);

    // �������
    while (continuationPoint.length() > 0)
    {
        printf("\nContinuationPoint is set. BrowseNext...\n");
        // �����һ��
        result = m_pSession->browseNext(
            serviceSettings,
            OpcUa_False,
            continuationPoint,
            referenceDescriptions);

        if (result.isGood())
        {
            // ��ӡ���
            printBrowseResults(referenceDescriptions);
        }
        else
        {
            // �������ʧ��
            printf("BrowseNext failed with status %s\n", result.toString().toUtf8());
        }
    }

    return result;
}

// �������ص�����objectNodeId��methodNodeId�����������޲���
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClient::callMethodInternal(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId)
{
    UaStatus        result;
    ServiceSettings serviceSettings;
    CallIn          callRequest;
    CallOut         callResult;

    // ����ͷ����� NodeIds
    // ����������û�����õ��ò���
    callRequest.methodId = methodNodeId;
    callRequest.objectId = objectNodeId;

    printf("\nCalling method %s on object %s\n", methodNodeId.toString().toUtf8(), objectNodeId.toString().toUtf8());
    result = m_pSession->call(
        serviceSettings,
        callRequest,
        callResult);

    if (result.isGood())
    {
        // ���з���ɹ� - �����
        if (callResult.callResult.isGood())
        {
            printf("Call succeeded\n");
        }
        else
        {
            printf("Call failed with status %s\n", callResult.callResult.toString().toUtf8());
        }

    }
    else
    {
        // �������ʧ��
        printf("Call failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

// ���������������referenceDescriptions
// ʱ�䣺2021-10-20
// ��ע����
void CInoUAClient::printBrowseResults(const UaReferenceDescriptions& referenceDescriptions)
{
    OpcUa_UInt32 i;
    for (i = 0; i < referenceDescriptions.length(); i++)
    {
        printf("node: ");
        UaNodeId referenceTypeId(referenceDescriptions[i].ReferenceTypeId);
        printf("[Ref=%s] ", referenceTypeId.toString().toUtf8());
        UaQualifiedName browseName(referenceDescriptions[i].BrowseName);
        printf("%s ( ", browseName.toString().toUtf8());
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_Object) printf("Object ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_Variable) printf("Variable ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_Method) printf("Method ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_ObjectType) printf("ObjectType ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_VariableType) printf("VariableType ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_ReferenceType) printf("ReferenceType ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_DataType) printf("DataType ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_View) printf("View ");
        UaNodeId nodeId(referenceDescriptions[i].NodeId.NodeId);
        printf("[NodeId=%s] ", nodeId.toFullString().toUtf8());
        printf(")\n");
    }
}

// ���������֤����Ϣ
// ʱ�䣺2021-10-20
// ��ע����
void CInoUAClient::printCertificateData(const UaByteString& serverCertificate)
{
    // ��֤���ֽ��ַ�������� UaPkiCertificate ��
    UaPkiCertificate cert = UaPkiCertificate::fromDER(serverCertificate);

    printf("- CommonName              %s\n", cert.commonName().toUtf8());
    printf("- Issuer.commonName       %s\n", cert.issuer().commonName.toUtf8());
    printf("- Issuer.organization     %s\n", cert.issuer().organization.toUtf8());
    printf("- Issuer.organizationUnit %s\n", cert.issuer().organizationUnit.toUtf8());
    printf("- Issuer.state            %s\n", cert.issuer().state.toUtf8());
    printf("- Issuer.country          %s\n", cert.issuer().country.toUtf8());
    printf("- ValidFrom               %s\n", cert.validFrom().toString().toUtf8());
    printf("- ValidTo                 %s\n", cert.validTo().toString().toUtf8());
}

// �������ж��û�����֤��״̬
// ʱ�䣺2021-10-20
// ��ע����
int CInoUAClient::userAcceptCertificate()
{
    int result = 0;

    int ch = getchar();

    if (ch == 'y' || ch == 'Y')
    {
        result = 1;
    }
    else if (ch == 'p' || ch == 'P')
    {
        result = 2;
    }
    else
    {
        result = 0;
    }

    // �ӿ���̨��ն�ȡ������
    while (ch != '\n')
    {
        ch = getchar();
    }

    return result;
}
