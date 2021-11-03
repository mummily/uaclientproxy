#include "CInoSession.h"
#include "uasession.h"
#include "CInoSessionConfig.h"
#include "uadiscovery.h"
#include "uapkicertificate.h"
#include "uaplatformdefs.h"
#include "InoCommonDef.h"
#include "uadir.h"
#include "ScopeExit.h"
#include "CInoSessionCallback.h"
#include "CInoSubscriptionCallback.h"

CInoSession::CInoSession()
    : UaClientSdk::UaSession()
{
    m_pSessionCallback = new CInoSessionCallback(this);
    m_pSubscriptionCallback = new CInoSubscriptionCallback(this);
}

CInoSession::~CInoSession()
{
    // ɾ�����ض��Ķ���
    if (nullptr != m_pSubscription)
    {
        deleteSubscription();
    }

    // �Ͽ����ӣ�ɾ���Ự
    if (isConnected() != OpcUa_False)
    {
        ServiceSettings serviceSettings;
        __super::disconnect(serviceSettings, OpcUa_True);
    }
}

// ���������ÿͻ���������Ϣ
// ʱ�䣺2021-10-20
// ��ע����
void CInoSession::setConfiguration(CInoSessionConfig* pConfiguration)
{
    assert(nullptr != pConfiguration);

    if (m_pSessionConfig == pConfiguration)
        return;

    // m_pSubscription->setConfiguration(pConfiguration);

    DelAndNil(m_pSessionConfig);
    m_pSessionConfig = pConfiguration;
}

// ���������ҷ������������������Ϣ
// ʱ�䣺2021-10-20
// ��ע����
// m_pConfiguration->getDiscoveryUrl()
UaStatus CInoSession::discover(const UaString& sDiscoveryUrl)
{
    // ��ȡ���÷������б�
    printf("\nCall FindServers on Url %s\n", sDiscoveryUrl.toUtf8());

    UaDiscovery discovery;
    ServiceSettings serviceSettings;
    ClientSecurityInfo clientSecurityInfo;
    UaApplicationDescriptions applicationDescriptions;
    UaStatus result = discovery.findServers(
        serviceSettings,
        sDiscoveryUrl,
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

// �������ǰ����ӷ�����
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::connect()
{
    // ��ȫ����δ��ʼ�� - û�а�ȫ����
    SessionSecurityInfo sessionSecurityInfo;
    return connectInternal(m_pSessionConfig->getServerUrl(), sessionSecurityInfo);
}

// ��������ȫ���ӷ�����
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::connectSecure()
{
    UaStatus result;
    SessionSecurityInfo sessionSecurityInfo;

    //************************************************
    // ���� 1 - ���ػ򴴽��ͻ���֤��
    //************************************************
    // ���ػ򴴽��ͻ���֤�鰲ȫ������Ҫ�ͻ��˺ͷ������˵�֤��
    // setupSecurity ���ؿͻ���֤�鲢��ʼ��֤��洢
    result = m_pSessionConfig->setupSecurity(sessionSecurityInfo);

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
        result = connectInternal(m_pSessionConfig->getServerUrl(), sessionSecurityInfo);

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
UaStatus CInoSession::connectInternal(const UaString& serverUrl, SessionSecurityInfo& sessionSecurityInfo)
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
    sessionConnectInfo.sApplicationName = m_pSessionConfig->getApplicationName();
    // ʹ������������Ψһ��Ӧ�ó��� URI
    sessionConnectInfo.sApplicationUri = UaString("urn:%1:%2:%3").arg(sNodeName).arg(COMPANY_NAME).arg(PRODUCT_NAME);
    sessionConnectInfo.sProductUri = UaString("urn:%1:%2").arg(COMPANY_NAME).arg(PRODUCT_NAME);
    sessionConnectInfo.sSessionName = sessionConnectInfo.sApplicationUri;
    sessionConnectInfo.bAutomaticReconnect = m_pSessionConfig->getAutomaticReconnect();
    sessionConnectInfo.bRetryInitialConnect = m_pSessionConfig->getRetryInitialConnect();

    // ���ӵ�������
    printf("\nConnecting to %s\n", serverUrl.toUtf8());
    result = __super::connect(
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
UaStatus CInoSession::writeInternal(const UaNodeIdArray& nodesToWrite, const UaVariantArray& valuesToWrite)
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
    result = __super::write(
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
UaStatus CInoSession::findSecureEndpoint(SessionSecurityInfo& sessionSecurityInfo)
{
    UaStatus result;
    ServiceSettings serviceSettings;
    ClientSecurityInfo clientSecurityInfo;
    UaEndpointDescriptions endpointDescriptions;
    UaDiscovery discovery;
    OpcUa_UInt32 bestSecurityIndex = 0;
    UaString sTemp;

    printf("\nTry to find secure Endpoint on: %s\n", m_pSessionConfig->getServerUrl().toUtf8());
    result = discovery.getEndpoints(
        serviceSettings,
        m_pSessionConfig->getServerUrl(),
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
UaStatus CInoSession::checkServerCertificateTrust(SessionSecurityInfo& sessionSecurityInfo)
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
UaStatus CInoSession::disconnect()
{
    ServiceSettings serviceSettings;

    printf("\nDisconnecting ...\n");
    UaStatus result = __super::disconnect(
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
UaStatus CInoSession::browseSimple()
{
    // �Ӹ��ļ��������û���������Ʒ���
    UaNodeId nodeToBrowse = UaNodeId(OpcUaId_RootFolder);
    UaStatus result = browseInternal(nodeToBrowse, 0);

    return result;
}

// �������������
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::browseContinuationPoint()
{
    UaNodeId nodeToBrowse = UaNodeId("Demo", 2);
    UaStatus result = browseInternal(nodeToBrowse, 5);
    return result;
}

// ���������������ļ����ڵ���ж�ֵ
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::read(const UaNodeIdArray& nodes)
{
    // UaNodeIdArray nodes = m_pConfiguration->getNodesToRead();

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
    UaStatus result = __super::read(
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
UaStatus CInoSession::write(const UaNodeIdArray& nodes, const UaVariantArray& values)
{
    UaStatus result;

    result = writeInternal(
        nodes,
        values);

    return result;
}

// ��������ע��Ľڵ�д��ֵ
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::writeRegistered(const UaVariantArray& values)
{
    UaStatus result;

    result = writeInternal(
        m_registeredNodes,
        values);

    return result;
}

// �������ڷ������ϴ������ĺͼ�����
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::subscribe()
{
    UaStatus result;
    result = createSubscriptionMonitors();
    return result;
}

// �������ڷ�������ɾ������
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::deleteSubscription()
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
    result = __super::deleteSubscription(
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

// �������ڷ��������˶�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::unsubscribe()
{
    return deleteSubscription();
}

// ����������ע��ڵ�
// ʱ�䣺2021-10-29
// ��ע����
UaStatus CInoSession::reRegisterNodes()
{
    return registerNodes(m_registeredNodes);
}

// ������ע��ڵ㣬Ĭ��ע������Ҫд��Ľڵ�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::registerNodes(const UaNodeIdArray& nodesToRegister)
{
    // ע������Ҫд��Ľڵ�
    // UaNodeIdArray nodesToRegister = m_pConfiguration->getNodesToWrite();

    printf("\nRegisterNodes...\n");
    ServiceSettings serviceSettings;
    UaStatus result = __super::registerNodes(
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
        printf("Original NodeId[%d]: %s\tRegistered NodeId[%d]: %s\n",
            i,
            UaNodeId(nodesToRegister[i]).toXmlString().toUtf8(),
            i,
            UaNodeId(m_registeredNodes[i]).toXmlString().toUtf8());
    }

    return result;
}

// ������ע���ڵ�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::unregisterNodes()
{
    ServiceSettings serviceSettings;

    // ע������֮ǰע������нڵ�
    printf("\nUnregisterNodes...\n");
    UaStatus result = __super::unregisterNodes(
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
UaStatus CInoSession::callMethodList(const UaNodeIdArray& objectNodeIds,
    const UaNodeIdArray& methodNodeIds,
    UaStatusArray& results)
{
    results.create(methodNodeIds.length());

    UaStatus result = OpcUa_Bad;

    for (OpcUa_UInt32 i = 0; i < methodNodeIds.length(); i++)
    {
        UaStatus stat = callMethod(objectNodeIds[i], methodNodeIds[i]);
        results[i] = stat;

        if (result.isNotGood())
            result = stat;
    }

    return result;
}

// ������TODO
// ʱ�䣺2021-10-27
// ��ע����
UaStatus CInoSession::updateNamespaceIndexes()
{
    return m_pSessionConfig->updateNamespaceIndexes(getNamespaceTable());
}

// �������ӽڵ�nodeToBrowse�����ַ�ռ�
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::browseInternal(const UaNodeId& nodeToBrowse, OpcUa_UInt32 maxReferencesToReturn)
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
    UaStatus result = __super::browse(
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
        result = __super::browseNext(
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
UaStatus CInoSession::callMethod(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId)
{
    // ����
    CallIn callRequest;
    callRequest.methodId = methodNodeId;
    callRequest.objectId = objectNodeId;
    // ���
    CallOut callResult;
    // δ���õ��ò���

    // ��������
    ServiceSettings serviceSettings;
    printf("\nCalling method %s on object %s\n", methodNodeId.toString().toUtf8(), objectNodeId.toString().toUtf8());
    UaStatus result = __super::call(
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
void CInoSession::printBrowseResults(const UaReferenceDescriptions& referenceDescriptions)
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
void CInoSession::printCertificateData(const UaByteString& serverCertificate)
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
int CInoSession::userAcceptCertificate()
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


// �������ڷ������ϴ������ġ�������
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::createSubscriptionMonitors(bool bDeleteSubscription/* = false*/)
{
    UaStatus result;

    // ɾ�����ж���
    if (bDeleteSubscription && nullptr != m_pSubscription)
    {
        deleteSubscription();
    }

    // �����¶���
    result = createSubscription();

    // ���������
    if (result.isGood())
    {
        result = createMonitoredItems(m_pSessionConfig->getEventTypeToFilter());
    }

    return result;
}

// �������ڷ������ϴ�������
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::createSubscription()
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
    UaStatus result = __super::createSubscription(
        serviceSettings,
        m_pSubscriptionCallback,
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

// �������ڶ����д����ܼ�ص���Ŀ
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoSession::createMonitoredItems(const UaNodeId& eventTypeToFilter)
{
#pragma TODO("CInoSubscription::createMonitoredItems �ٿ�")
    if (m_pSubscription == nullptr)
    {
        printf("\nError: No Subscription created\n");
        return OpcUa_BadInvalidState;
    }

    UaMonitoredItemCreateRequests itemsToCreate;

    // ����һ���¼���������������ʹ�÷���������
    itemsToCreate.create(1);
    itemsToCreate[0].ItemToMonitor.AttributeId = OpcUa_Attributes_EventNotifier;
    itemsToCreate[0].ItemToMonitor.NodeId.Identifier.Numeric = OpcUaId_Server;
    itemsToCreate[0].RequestedParameters.ClientHandle = 0;
    itemsToCreate[0].RequestedParameters.SamplingInterval = 0;
    itemsToCreate[0].RequestedParameters.QueueSize = 0;
    itemsToCreate[0].RequestedParameters.DiscardOldest = OpcUa_True;
    itemsToCreate[0].MonitoringMode = OpcUa_MonitoringMode_Reporting;

    // ������ÿ���¼�һ���͵��¼��ֶ�
    UaEventFilter eventFilter;
    UaSimpleAttributeOperand selectElement;
    selectElement.setBrowsePathElement(0, UaQualifiedName("Message", 0), 1);
    eventFilter.setSelectClauseElement(0, selectElement, 3);
    selectElement.setBrowsePathElement(0, UaQualifiedName("SourceName", 0), 1);
    eventFilter.setSelectClauseElement(1, selectElement, 3);
    selectElement.setBrowsePathElement(0, UaQualifiedName("Severity", 0), 1);
    eventFilter.setSelectClauseElement(2, selectElement, 3);

    // ���� ControllerEventType ���͵��¼�
    UaContentFilterElement* pContentFilterElement = new UaContentFilterElement;

    // OfType������
    pContentFilterElement->setFilterOperator(OpcUa_FilterOperator_OfType);

    // 1 (Literal)������
    UaFilterOperand* pOperand = new UaLiteralOperand;
    ((UaLiteralOperand*)pOperand)->setLiteralValue(eventTypeToFilter);
    pContentFilterElement->setFilterOperand(0, pOperand, 1);

    UaContentFilter* pContentFilter = new UaContentFilter;
    pContentFilter->setContentFilterElement(0, pContentFilterElement, 1);
    eventFilter.setWhereClause(pContentFilter);

    // Ϊ�����Ŀ���ù�����
    eventFilter.detachFilter(itemsToCreate[0].RequestedParameters.Filter);

    ServiceSettings serviceSettings;
    UaMonitoredItemCreateResults createResults;
    printf("\nAdding monitored items to subscription ...\n");
    UaStatus result = m_pSubscription->createMonitoredItems(
        serviceSettings,
        OpcUa_TimestampsToReturn_Both,
        itemsToCreate,
        createResults);

    // ����ʧ��
    if (result.isNotGood())
    {
        printf("CreateMonitoredItems failed with status %s\n", result.toString().toUtf8());
        return result;
    }

    // ���óɹ��������
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
