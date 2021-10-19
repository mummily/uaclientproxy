#include "sampleclient.h"
#include "uasession.h"
#include "samplesubscription.h"
#include "configuration.h"
#include "uadiscovery.h"
#include "uapkicertificate.h"
#include "uaplatformdefs.h"

SampleClient::SampleClient()
{
    m_pSession = new UaSession();
    m_pConfiguration = new Configuration();
    m_pSampleSubscription = new SampleSubscription(m_pConfiguration);
}

SampleClient::~SampleClient()
{
    if (m_pSampleSubscription)
    {
        // ɾ�����ض��Ķ���
        delete m_pSampleSubscription;
        m_pSampleSubscription = nullptr;
    }

    if (m_pSession)
    {
        // ����Ự��Ȼ���ӣ���Ͽ�����
        if (m_pSession->isConnected() != OpcUa_False)
        {
            ServiceSettings serviceSettings;
            m_pSession->disconnect(serviceSettings, OpcUa_True);
        }
        delete m_pSession;
        m_pSession = nullptr;
    }

    if (m_pConfiguration)
    {
        delete m_pConfiguration;
        m_pConfiguration = nullptr;
    }
}

void SampleClient::connectionStatusChanged(
    OpcUa_UInt32             clientConnectionId,
    UaClient::ServerStatus   serverStatus)
{
    OpcUa_ReferenceParameter(clientConnectionId);

    printf("-------------------------------------------------------------\n");
    switch (serverStatus)
    {
    case UaClient::Disconnected:
        printf("Connection status changed to Disconnected\n");
        break;
    case UaClient::Connected:
        printf("Connection status changed to Connected\n");
        if (m_serverStatus != UaClient::NewSessionCreated)
        {
            m_pConfiguration->updateNamespaceIndexes(m_pSession->getNamespaceTable());
        }
        break;
    case UaClient::ConnectionWarningWatchdogTimeout:
        printf("Connection status changed to ConnectionWarningWatchdogTimeout\n");
        break;
    case UaClient::ConnectionErrorApiReconnect:
        printf("Connection status changed to ConnectionErrorApiReconnect\n");
        break;
    case UaClient::ServerShutdown:
        printf("Connection status changed to ServerShutdown\n");
        break;
    case UaClient::NewSessionCreated:
        printf("Connection status changed to NewSessionCreated\n");
        m_pConfiguration->updateNamespaceIndexes(m_pSession->getNamespaceTable());
        // ��ע��Ľڵ����»Ự�в�����Ч
        registerNodes();
        break;
    }
    printf("-------------------------------------------------------------\n");

    m_serverStatus = serverStatus;
}

void SampleClient::setConfiguration(Configuration* pConfiguration)
{
    if (m_pSampleSubscription)
    {
        m_pSampleSubscription->setConfiguration(pConfiguration);
    }
    if (m_pConfiguration)
    {
        delete m_pConfiguration;
    }
    m_pConfiguration = pConfiguration;
}

UaStatus SampleClient::discover()
{
    UaStatus result;
    UaDiscovery discovery;
    ServiceSettings serviceSettings;
    ClientSecurityInfo clientSecurityInfo;
    UaApplicationDescriptions applicationDescriptions;
    UaEndpointDescriptions endpointDescriptions;
    OpcUa_UInt32 i, j;
    OpcUa_Int32 k;
    UaString sTemp;

    // ��ȡ���÷������б�
    printf("\nCall FindServers on Url %s\n", m_pConfiguration->getDiscoveryUrl().toUtf8());
    result = discovery.findServers(
        serviceSettings,
        m_pConfiguration->getDiscoveryUrl(),
        clientSecurityInfo,
        applicationDescriptions);

    if (result.isGood())
    {
        // ��ӡ�������б�
        printf("\nFindServers succeeded\n");
        for (i = 0; i < applicationDescriptions.length(); i++)
        {
            printf("** Application [%d] **********************************************************\n", i);
            sTemp = &applicationDescriptions[i].ApplicationUri;
            printf(" ApplicationUri       %s\n", sTemp.toUtf8());
            sTemp = &applicationDescriptions[i].ApplicationName.Text;
            printf(" ApplicationName      %s\n", sTemp.toUtf8());
            for (k = 0; k < applicationDescriptions[i].NoOfDiscoveryUrls; k++)
            {
                UaString sDiscoveryUrl(applicationDescriptions[i].DiscoveryUrls[k]);
                printf("** DiscoveryUrl [%s] ***********************\n", sDiscoveryUrl.toUtf8());
                // ����ÿ����������ȡ���ö˵���б�
                result = discovery.getEndpoints(
                    serviceSettings,
                    sDiscoveryUrl,
                    clientSecurityInfo,
                    endpointDescriptions);

                if (result.isGood())
                {
                    // ��ӡ�˵��б�
                    for (j = 0; j < endpointDescriptions.length(); j++)
                    {
                        printf("** Endpoint[%d] ***********************************************\n", j);
                        sTemp = &endpointDescriptions[j].EndpointUrl;
                        printf(" Endpoint URL     %s\n", sTemp.toUtf8());
                        sTemp = &endpointDescriptions[j].SecurityPolicyUri;
                        printf(" Security Policy  %s\n", sTemp.toUtf8());
                        sTemp = "Invalid";
                        if ( endpointDescriptions[j].SecurityMode == OpcUa_MessageSecurityMode_None )
                        {
                            sTemp = "None";
                        }
                        if ( endpointDescriptions[j].SecurityMode == OpcUa_MessageSecurityMode_Sign )
                        {
                            sTemp = "Sign";
                        }
                        if ( endpointDescriptions[j].SecurityMode == OpcUa_MessageSecurityMode_SignAndEncrypt )
                        {
                            sTemp = "SignAndEncrypt";
                        }
                        printf(" Security Mode    %s\n", sTemp.toUtf8());
                        printf("**************************************************************\n");
                    }
                }
                else
                {
                    printf("GetEndpoints failed with status %s\n", result.toString().toUtf8());
                }
                printf("************************************************************************\n");
            }
            printf("******************************************************************************\n");
        }
    }
    else
    {
        printf("FindServers failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

OpcUa_Boolean SampleClient::isConnected() const
{
    return m_pSession->isConnected();
}

UaStatus SampleClient::connect(const UaString& sURL)
{
    UaStatus result;

    // �ṩ�йؿͻ��˵���Ϣ
    SessionConnectInfo sessionConnectInfo;
    UaString sNodeName("unknown_host");
    char szHostName[256];
    if (0 == UA_GetHostname(szHostName, 256))
    {
        sNodeName = szHostName;
    }
    sessionConnectInfo.sApplicationName = "Unified Automation Getting Started Client";
    // ʹ������������Ψһ��Ӧ�ó��� URI
    sessionConnectInfo.sApplicationUri  = UaString("urn:%1:UnifiedAutomation:GettingStartedClient").arg(sNodeName);
    sessionConnectInfo.sProductUri      = "urn:UnifiedAutomation:GettingStartedClient";
    sessionConnectInfo.sSessionName     = sessionConnectInfo.sApplicationUri;

    // ��ȫ����δ��ʼ�� - ��ʱû�а�ȫ����
    SessionSecurityInfo sessionSecurityInfo;

    printf("\nConnecting to %s\n", sURL.toUtf8());
    result = m_pSession->connect(
        sURL,
        sessionConnectInfo,
        sessionSecurityInfo,
        this);

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

UaStatus SampleClient::connect()
{
    // ��ȫ����δ��ʼ�� - û�а�ȫ����
    SessionSecurityInfo sessionSecurityInfo;

    return connectInternal(m_pConfiguration->getServerUrl(), sessionSecurityInfo);
}

UaStatus SampleClient::connectSecure()
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

UaStatus SampleClient::connectInternal(const UaString& serverUrl, SessionSecurityInfo& sessionSecurityInfo)
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
        this);

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

UaStatus SampleClient::writeInternal(const UaNodeIdArray& nodesToWrite, const UaVariantArray& valuesToWrite)
{
    UaStatus            result;
    ServiceSettings     serviceSettings;
    UaWriteValues       writeValues;
    UaStatusCodeArray   results;
    UaDiagnosticInfos   diagnosticInfos;

    // �������
    if (nodesToWrite.length() != valuesToWrite.length())
    {
        return OpcUa_BadInvalidArgument;
    }

    // ��������д�����нڵ�
    writeValues.create(nodesToWrite.length());

    for (OpcUa_UInt32 i = 0; i < writeValues.length(); i++)
    {
        writeValues[i].AttributeId = OpcUa_Attributes_Value;
        OpcUa_NodeId_CopyTo(&nodesToWrite[i], &writeValues[i].NodeId);
        // ����Ҫд���ֵ
        OpcUa_Variant_CopyTo(&valuesToWrite[i], &writeValues[i].Value.Value);
    }

    printf("\nWriting...\n");
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

UaStatus SampleClient::findSecureEndpoint(SessionSecurityInfo& sessionSecurityInfo)
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
            if ( endpointDescriptions[bestSecurityIndex].SecurityMode == OpcUa_MessageSecurityMode_None )
            {
                sTemp = "None";
            }
            if ( endpointDescriptions[bestSecurityIndex].SecurityMode == OpcUa_MessageSecurityMode_Sign )
            {
                sTemp = "Sign";
            }
            if ( endpointDescriptions[bestSecurityIndex].SecurityMode == OpcUa_MessageSecurityMode_SignAndEncrypt )
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

UaStatus SampleClient::checkServerCertificateTrust(SessionSecurityInfo& sessionSecurityInfo)
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

UaStatus SampleClient::disconnect()
{
    UaStatus result;

    ServiceSettings serviceSettings;

    printf("\nDisconnecting ...\n");
    result = m_pSession->disconnect(
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

UaStatus SampleClient::browseSimple()
{
    UaStatus result;
    UaNodeId nodeToBrowse;

    // �Ӹ��ļ��������û���������Ʒ���
    nodeToBrowse = UaNodeId(OpcUaId_RootFolder);
    result = browseInternal(nodeToBrowse, 0);

    return result;
}

UaStatus SampleClient::browseContinuationPoint()
{
    UaStatus result;
    UaNodeId nodeToBrowse;

    // �� Massfolder �����������÷�������Ϊ 5
    nodeToBrowse = UaNodeId("Demo", 2);
    result = browseInternal(nodeToBrowse, 5);

    return result;
}

UaStatus SampleClient::read()
{
    UaStatus          result;
    ServiceSettings   serviceSettings;
    UaReadValueIds    nodesToRead;
    UaDataValues      values;
    UaDiagnosticInfos diagnosticInfos;

    // �������ж�ȡ���нڵ�
    UaNodeIdArray nodes = m_pConfiguration->getNodesToRead();
    nodesToRead.create(nodes.length());

    for (OpcUa_UInt32 i = 0; i < nodes.length(); i++)
    {
        nodesToRead[i].AttributeId = OpcUa_Attributes_Value;
        OpcUa_NodeId_CopyTo(&nodes[i], &nodesToRead[i].NodeId);
    }

    printf("\nReading ...\n");
    result = m_pSession->read(
        serviceSettings,
        0,
        OpcUa_TimestampsToReturn_Both,
        nodesToRead,
        values,
        diagnosticInfos);

    if (result.isGood())
    {
        // Read service succeded - check individual status codes
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
    }
    else
    {
        // �������ʧ��
        printf("Read failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

UaStatus SampleClient::write()
{
    UaStatus result;

    // ��������д�����нڵ�
    result = writeInternal(
        m_pConfiguration->getNodesToWrite(),
        m_pConfiguration->getWriteValues());

    return result;
}

UaStatus SampleClient::writeRegistered()
{
    UaStatus result;

    // д������ע��ڵ�
    result = writeInternal(
        m_registeredNodes,
        m_pConfiguration->getWriteValues());

    return result;
}

UaStatus SampleClient::subscribe()
{
    UaStatus result;

    result = m_pSampleSubscription->createSubscription(m_pSession);
    if ( result.isGood() )
    {
        result = m_pSampleSubscription->createMonitoredItems();
    }
    return result;
}

UaStatus SampleClient::unsubscribe()
{
    return m_pSampleSubscription->deleteSubscription();
}

UaStatus SampleClient::registerNodes()
{
    UaStatus            result;
    ServiceSettings     serviceSettings;
    UaNodeIdArray       nodesToRegister;

    // ע�����нڵ��Դ�������д��
    nodesToRegister = m_pConfiguration->getNodesToWrite();
    printf("\nRegisterNodes...\n");
    result = m_pSession->registerNodes(
        serviceSettings,
        nodesToRegister,
        m_registeredNodes);

    if (result.isGood())
    {
        // ע��ڵ����ɹ�
        printf("RegisterNodes succeeded\n");

        for (OpcUa_UInt32 i = 0; i < nodesToRegister.length(); i++)
        {
            printf("Original NodeId[%d]: %s\tRegistered NodeId[%d]: %s\n", i, UaNodeId(nodesToRegister[i]).toXmlString().toUtf8(), i, UaNodeId(m_registeredNodes[i]).toXmlString().toUtf8());
        }
    }
    else
    {
        // �������ʧ��
        printf("RegisterNodes failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

UaStatus SampleClient::unregisterNodes()
{
    UaStatus            result;
    ServiceSettings     serviceSettings;

    // ע������֮ǰע������нڵ�
    printf("\nUnregisterNodes...\n");
    result = m_pSession->unregisterNodes(
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

UaStatus SampleClient::callMethods()
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

UaStatus SampleClient::browseInternal(const UaNodeId& nodeToBrowse, OpcUa_UInt32 maxReferencesToReturn)
{
    UaStatus result;

    ServiceSettings serviceSettings;
    BrowseContext browseContext;
    UaByteString continuationPoint;
    UaReferenceDescriptions referenceDescriptions;

    // ����browseContext
    browseContext.browseDirection = OpcUa_BrowseDirection_Forward;
    browseContext.referenceTypeId = OpcUaId_HierarchicalReferences;
    browseContext.includeSubtype = OpcUa_True;
    browseContext.maxReferencesToReturn = maxReferencesToReturn;

    printf("\nBrowsing from Node %s...\n", nodeToBrowse.toXmlString().toUtf8());
    result = m_pSession->browse(
        serviceSettings,
        nodeToBrowse,
        browseContext,
        continuationPoint,
        referenceDescriptions);

    if (result.isGood())
    {
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
    }
    else
    {
        // �������ʧ��
        printf("Browse failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

UaStatus SampleClient::callMethodInternal(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId)
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

void SampleClient::printBrowseResults(const UaReferenceDescriptions& referenceDescriptions)
{
    OpcUa_UInt32 i;
    for (i=0; i<referenceDescriptions.length(); i++)
    {
        printf("node: ");
        UaNodeId referenceTypeId(referenceDescriptions[i].ReferenceTypeId);
        printf("[Ref=%s] ", referenceTypeId.toString().toUtf8() );
        UaQualifiedName browseName(referenceDescriptions[i].BrowseName);
        printf("%s ( ", browseName.toString().toUtf8() );
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_Object) printf("Object ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_Variable) printf("Variable ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_Method) printf("Method ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_ObjectType) printf("ObjectType ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_VariableType) printf("VariableType ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_ReferenceType) printf("ReferenceType ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_DataType) printf("DataType ");
        if (referenceDescriptions[i].NodeClass & OpcUa_NodeClass_View) printf("View ");
        UaNodeId nodeId(referenceDescriptions[i].NodeId.NodeId);
        printf("[NodeId=%s] ", nodeId.toFullString().toUtf8() );
        printf(")\n");
    }
}

void SampleClient::printCertificateData(const UaByteString& serverCertificate)
{
    // ��֤���ֽ��ַ�������� UaPkiCertificate ��
    UaPkiCertificate cert = UaPkiCertificate::fromDER(serverCertificate);

    printf("- CommonName              %s\n", cert.commonName().toUtf8() );
    printf("- Issuer.commonName       %s\n", cert.issuer().commonName.toUtf8() );
    printf("- Issuer.organization     %s\n", cert.issuer().organization.toUtf8() );
    printf("- Issuer.organizationUnit %s\n", cert.issuer().organizationUnit.toUtf8() );
    printf("- Issuer.state            %s\n", cert.issuer().state.toUtf8() );
    printf("- Issuer.country          %s\n", cert.issuer().country.toUtf8() );
    printf("- ValidFrom               %s\n", cert.validFrom().toString().toUtf8() );
    printf("- ValidTo                 %s\n", cert.validTo().toString().toUtf8() );
}

int SampleClient::userAcceptCertificate()
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
