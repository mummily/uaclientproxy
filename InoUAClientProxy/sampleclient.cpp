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
        // 删除本地订阅对象
        delete m_pSampleSubscription;
        m_pSampleSubscription = nullptr;
    }

    if (m_pSession)
    {
        // 如果会话仍然连接，则断开连接
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
        // 已注册的节点在新会话中不再有效
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

    // 获取可用服务器列表
    printf("\nCall FindServers on Url %s\n", m_pConfiguration->getDiscoveryUrl().toUtf8());
    result = discovery.findServers(
        serviceSettings,
        m_pConfiguration->getDiscoveryUrl(),
        clientSecurityInfo,
        applicationDescriptions);

    if (result.isGood())
    {
        // 打印服务器列表
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
                // 对于每个服务器获取可用端点的列表
                result = discovery.getEndpoints(
                    serviceSettings,
                    sDiscoveryUrl,
                    clientSecurityInfo,
                    endpointDescriptions);

                if (result.isGood())
                {
                    // 打印端点列表
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

    // 提供有关客户端的信息
    SessionConnectInfo sessionConnectInfo;
    UaString sNodeName("unknown_host");
    char szHostName[256];
    if (0 == UA_GetHostname(szHostName, 256))
    {
        sNodeName = szHostName;
    }
    sessionConnectInfo.sApplicationName = "Unified Automation Getting Started Client";
    // 使用主机名生成唯一的应用程序 URI
    sessionConnectInfo.sApplicationUri  = UaString("urn:%1:UnifiedAutomation:GettingStartedClient").arg(sNodeName);
    sessionConnectInfo.sProductUri      = "urn:UnifiedAutomation:GettingStartedClient";
    sessionConnectInfo.sSessionName     = sessionConnectInfo.sApplicationUri;

    // 安全设置未初始化 - 暂时没有安全连接
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
    // 安全设置未初始化 - 没有安全连接
    SessionSecurityInfo sessionSecurityInfo;

    return connectInternal(m_pConfiguration->getServerUrl(), sessionSecurityInfo);
}

UaStatus SampleClient::connectSecure()
{
    UaStatus result;
    SessionSecurityInfo sessionSecurityInfo;

    //************************************************
    // 步骤 1 - 加载或创建客户端证书
    //************************************************
    // 加载或创建客户端证书安全连接需要客户端和服务器端的证书
    // setupSecurity 加载客户端证书并初始化证书存储
    result = m_pConfiguration->setupSecurity(sessionSecurityInfo);

    //************************************************
    // 步骤 2 - 在服务器上查找安全端点
    //************************************************
    // 这通常在第一次使用服务器时完成
    // 设置 ServerCertificate、SecurityPolicyUri 和 SecurityMode 应与其他连接信息（如 URL）一起存储，以便在以后的连接中重用 
    if (result.isGood())
    {
        result = findSecureEndpoint(sessionSecurityInfo);
    }

    //************************************************
    // 步骤 3 - 验证服务器证书
    //************************************************
    // 这一步通常在第一次连接时是必需的（如步骤 2）
    // 如果服务器证书在信任列表中，则连接检查成功 
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

    // 提供有关客户的信息
    SessionConnectInfo sessionConnectInfo;
    UaString sNodeName("unknown_host");
    char szHostName[256];
    if (0 == UA_GetHostname(szHostName, 256))
    {
        sNodeName = szHostName;
    }

    // 使用配置中的数据填充会话连接信息
    sessionConnectInfo.sApplicationName = m_pConfiguration->getApplicationName();
    // 使用主机名生成唯一的应用程序 URI
    sessionConnectInfo.sApplicationUri = UaString("urn:%1:%2:%3").arg(sNodeName).arg(COMPANY_NAME).arg(PRODUCT_NAME);
    sessionConnectInfo.sProductUri = UaString("urn:%1:%2").arg(COMPANY_NAME).arg(PRODUCT_NAME);
    sessionConnectInfo.sSessionName = sessionConnectInfo.sApplicationUri;
    sessionConnectInfo.bAutomaticReconnect = m_pConfiguration->getAutomaticReconnect();
    sessionConnectInfo.bRetryInitialConnect = m_pConfiguration->getRetryInitialConnect();

    // 连接到服务器
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

    // 检入参数
    if (nodesToWrite.length() != valuesToWrite.length())
    {
        return OpcUa_BadInvalidArgument;
    }

    // 从配置中写入所有节点
    writeValues.create(nodesToWrite.length());

    for (OpcUa_UInt32 i = 0; i < writeValues.length(); i++)
    {
        writeValues[i].AttributeId = OpcUa_Attributes_Value;
        OpcUa_NodeId_CopyTo(&nodesToWrite[i], &writeValues[i].NodeId);
        // 设置要写入的值
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
        // 写入服务成功 - 检查各个状态代码
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
        // 服务调用失败
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

        // 选择安全性最好的端点
        for (i = 0; i < endpointDescriptions.length(); i++)
        {
            if (endpointDescriptions[i].SecurityLevel > securityLevel)
            {
                bestSecurityIndex = i;
                securityLevel = endpointDescriptions[i].SecurityLevel;
            }
        }

        // 检查找到的端点是否是安全端点
        if (endpointDescriptions[bestSecurityIndex].SecurityMode < OpcUa_MessageSecurityMode_Sign)
        {
            printf("No secure endpoint available on server\n");
            result = OpcUa_BadSecurityConfig;
        }
        // 打印找到的安全端点
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

            // 以下设置应与服务器配置集服务器证书一起存储
            sessionSecurityInfo.serverCertificate = endpointDescriptions[bestSecurityIndex].ServerCertificate;
            // 设置安全模式和安全策略
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

    // 处理验证错误需要以下步骤：
    // 1. 出示证书并要求用户接受证书
    // 2. 用户可以拒绝、暂时接受或永久接受
    // 3. 接受时将服务器证书永久复制到客户端信任列表
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
            // 已经验证了上面的证书在连接期间跳过验证，暂时接受
            sessionSecurityInfo.doServerCertificateVerify = OpcUa_False;
        }
        else if (accept == 2)
        {
            // 将服务器证书复制到客户端信任列表中
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
            // 将证书存储在信任列表中 - 可以在连接期间验证证书
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

    // 从根文件夹浏览，没有引用限制返回
    nodeToBrowse = UaNodeId(OpcUaId_RootFolder);
    result = browseInternal(nodeToBrowse, 0);

    return result;
}

UaStatus SampleClient::browseContinuationPoint()
{
    UaStatus result;
    UaNodeId nodeToBrowse;

    // 从 Massfolder 浏览，最大引用返回设置为 5
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

    // 从配置中读取所有节点
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
        // 服务调用失败
        printf("Read failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

UaStatus SampleClient::write()
{
    UaStatus result;

    // 从配置中写入所有节点
    result = writeInternal(
        m_pConfiguration->getNodesToWrite(),
        m_pConfiguration->getWriteValues());

    return result;
}

UaStatus SampleClient::writeRegistered()
{
    UaStatus result;

    // 写入所有注册节点
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

    // 注册所有节点以从配置中写入
    nodesToRegister = m_pConfiguration->getNodesToWrite();
    printf("\nRegisterNodes...\n");
    result = m_pSession->registerNodes(
        serviceSettings,
        nodesToRegister,
        m_registeredNodes);

    if (result.isGood())
    {
        // 注册节点服务成功
        printf("RegisterNodes succeeded\n");

        for (OpcUa_UInt32 i = 0; i < nodesToRegister.length(); i++)
        {
            printf("Original NodeId[%d]: %s\tRegistered NodeId[%d]: %s\n", i, UaNodeId(nodesToRegister[i]).toXmlString().toUtf8(), i, UaNodeId(m_registeredNodes[i]).toXmlString().toUtf8());
        }
    }
    else
    {
        // 服务调用失败
        printf("RegisterNodes failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

UaStatus SampleClient::unregisterNodes()
{
    UaStatus            result;
    ServiceSettings     serviceSettings;

    // 注销我们之前注册的所有节点
    printf("\nUnregisterNodes...\n");
    result = m_pSession->unregisterNodes(
        serviceSettings,
        m_registeredNodes);

    if (result.isGood())
    {
        // 注册节点服务成功
        printf("UnregisterNodes succeeded\n");
    }
    else
    {
        // 服务调用失败
        printf("UnregisterNodes failed with status %s\n", result.toString().toUtf8());
    }

    return result;
}

UaStatus SampleClient::callMethods()
{
    UaStatus result;

    // 从配置中调用所有方法
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

    // 配置browseContext
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
        // 打印结果
        printBrowseResults(referenceDescriptions);

        // 继续浏览
        while (continuationPoint.length() > 0)
        {
            printf("\nContinuationPoint is set. BrowseNext...\n");
            // 浏览下一个
            result = m_pSession->browseNext(
                serviceSettings,
                OpcUa_False,
                continuationPoint,
                referenceDescriptions);

            if (result.isGood())
            {
                // 打印结果
                printBrowseResults(referenceDescriptions);
            }
            else
            {
                // 服务调用失败
                printf("BrowseNext failed with status %s\n", result.toString().toUtf8());
            }
        }
    }
    else
    {
        // 服务调用失败
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

    // 对象和方法的 NodeIds
    // 我们在这里没有设置调用参数
    callRequest.methodId = methodNodeId;
    callRequest.objectId = objectNodeId;

    printf("\nCalling method %s on object %s\n", methodNodeId.toString().toUtf8(), objectNodeId.toString().toUtf8());
    result = m_pSession->call(
        serviceSettings,
        callRequest,
        callResult);

    if (result.isGood())
    {
        // 呼叫服务成功 - 检查结果
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
        // 服务调用失败
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
    // 将证书字节字符串分配给 UaPkiCertificate 类
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

    // 从控制台清空读取缓冲区
    while (ch != '\n')
    {
        ch = getchar();
    }

    return result;
}
