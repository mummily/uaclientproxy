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

CInoUAClient::CInoUAClient()
{
    m_pSession = new UaSession();
    m_pSubscriptionCallback = new CInoUASubscriptionCallback(m_pSession, m_pConfiguration);
}

CInoUAClient::~CInoUAClient()
{
    // 删除本地订阅对象
    DelAndNil(m_pSubscriptionCallback);

    // 断开连接，删除会话
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

// 描述：连接状态变更回调函数
// 时间：2021-10-20
// 备注：无
void CInoUAClient::connectionStatusChanged(
    OpcUa_UInt32             clientConnectionId,
    UaClient::ServerStatus   serverStatus)
{
    OpcUa_ReferenceParameter(clientConnectionId);

    printf("-------------------------------------------------------------\n");
    SCOPE_EXIT(
        printf("-------------------------------------------------------------\n");
    );

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

    m_serverStatus = serverStatus;
}

// 描述：设置客户端配置信息
// 时间：2021-10-20
// 备注：无
void CInoUAClient::setConfiguration(CInoUAClientConfig* pConfiguration)
{
    assert(nullptr != pConfiguration);

    if (m_pConfiguration == pConfiguration)
        return;

    m_pSubscriptionCallback->setConfiguration(pConfiguration);

    DelAndNil(m_pConfiguration);
    m_pConfiguration = pConfiguration;
}

// 描述：查找服务器并输出服务器信息
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::discover()
{
    // 获取可用服务器列表
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

    // 打印服务器列表
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

            // 对于每个服务器获取可用端点的列表
            UaEndpointDescriptions endpointDescriptions;
            result = discovery.getEndpoints(
                serviceSettings,
                sDiscoveryUrl,
                clientSecurityInfo,
                endpointDescriptions);

            if (result.isGood())
            {
                // 打印端点列表
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

// 描述：客户端是否处于连接状态
// 时间：2021-10-20
// 备注：无
OpcUa_Boolean CInoUAClient::isConnected() const
{
    return m_pSession->isConnected();
}

// 描述：非安连接服务器
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::connect()
{
    // 安全设置未初始化 - 没有安全连接
    SessionSecurityInfo sessionSecurityInfo;
    return connectInternal(m_pConfiguration->getServerUrl(), sessionSecurityInfo);
}

// 描述：安全连接服务器
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::connectSecure()
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

// 描述：连接服务器，sessionConnectInfo读自配置
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::connectInternal(const UaString& serverUrl, SessionSecurityInfo& sessionSecurityInfo)
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

// 描述：节点nodesToWrite中写入valuesToWrite值
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::writeInternal(const UaNodeIdArray& nodesToWrite, const UaVariantArray& valuesToWrite)
{

    // 检入参数
    if (nodesToWrite.length() < 1
        || valuesToWrite.length() < 1)
    {
        return OpcUa_BadInvalidArgument;
    }

    // 从配置中写入所有节点
    UaWriteValues writeValues;
    writeValues.create(nodesToWrite.length());

    for (OpcUa_UInt32 i = 0; i < writeValues.length(); i++)
    {
        writeValues[i].AttributeId = OpcUa_Attributes_Value;
        OpcUa_NodeId_CopyTo(&nodesToWrite[i], &writeValues[i].NodeId);
        // 设置要写入的值
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

// 描述：在服务器上查找安全端点
// 时间：2021-10-20
// 备注：无
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

// 描述：验证服务器证书
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::checkServerCertificateTrust(SessionSecurityInfo& sessionSecurityInfo)
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

// 描述：断开连接
// 时间：2021-10-20
// 备注：无
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

// 描述：从根节点浏览节点
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::browseSimple()
{
    // 从根文件夹浏览，没有引用限制返回
    UaNodeId nodeToBrowse = UaNodeId(OpcUaId_RootFolder);
    UaStatus result = browseInternal(nodeToBrowse, 0);

    return result;
}

// 描述：继续浏览
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::browseContinuationPoint()
{
    UaNodeId nodeToBrowse = UaNodeId("Demo", 2);
    UaStatus result = browseInternal(nodeToBrowse, 5);
    return result;
}

// 描述：根据配置文件，节点进行读值
// 时间：2021-10-20
// 备注：无
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
        // 服务调用失败
        printf("Read failed with status %s\n", result.toString().toUtf8());
        return result;
    }

    // 读取服务成功 - 检查各个状态代码
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

// 描述：根据配置文件，节点进行写值
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::write()
{
    UaStatus result;

    result = writeInternal(
        m_pConfiguration->getNodesToWrite(),
        m_pConfiguration->getWriteValues());

    return result;
}

// 描述：给注册的节点写入值
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::writeRegistered()
{
    UaStatus result;

    result = writeInternal(
        m_registeredNodes,
        m_pConfiguration->getWriteValues());

    return result;
}

// 描述：在服务器上创建订阅和监视项
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::subscribe()
{
    UaStatus result;
    result = m_pSubscriptionCallback->createSubscriptionMonitors();
    return result;
}

// 描述：在服务器上退订
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::unsubscribe()
{
    return m_pSubscriptionCallback->deleteSubscription();
}

// 描述：注册节点，默认注册所有要写入的节点
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::registerNodes()
{
    // 注册所有要写入的节点
    UaNodeIdArray nodesToRegister = m_pConfiguration->getNodesToWrite();

    printf("\nRegisterNodes...\n");
    ServiceSettings serviceSettings;
    UaStatus result = m_pSession->registerNodes(
        serviceSettings,
        nodesToRegister,
        m_registeredNodes);

    if (result.isNotGood())
    {
        // 服务调用失败
        printf("RegisterNodes failed with status %s\n", result.toString().toUtf8());
        return result;
    }

    // 注册节点服务成功
    printf("RegisterNodes succeeded\n");
    for (OpcUa_UInt32 i = 0; i < nodesToRegister.length(); i++)
    {
        printf("Original NodeId[%d]: %s\tRegistered NodeId[%d]: %s\n", i, UaNodeId(nodesToRegister[i]).toXmlString().toUtf8(), i, UaNodeId(m_registeredNodes[i]).toXmlString().toUtf8());
    }

    return result;
}

// 描述：注销节点
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::unregisterNodes()
{
    ServiceSettings serviceSettings;

    // 注销我们之前注册的所有节点
    printf("\nUnregisterNodes...\n");
    UaStatus result = m_pSession->unregisterNodes(
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

// 描述：回调对象的方法，方法无参数
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::callMethods()
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

// 描述：从节点nodeToBrowse浏览地址空间
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::browseInternal(const UaNodeId& nodeToBrowse, OpcUa_UInt32 maxReferencesToReturn)
{
    // 配置browseContext
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
        // 服务调用失败
        printf("Browse failed with status %s\n", result.toString().toUtf8());
        return result;
    }

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

    return result;
}

// 描述：回调对象objectNodeId的methodNodeId方法，方法无参数
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClient::callMethodInternal(const UaNodeId& objectNodeId, const UaNodeId& methodNodeId)
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

// 描述：输出浏览结果referenceDescriptions
// 时间：2021-10-20
// 备注：无
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

// 描述：输出证书信息
// 时间：2021-10-20
// 备注：无
void CInoUAClient::printCertificateData(const UaByteString& serverCertificate)
{
    // 将证书字节字符串分配给 UaPkiCertificate 类
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

// 描述：判断用户接受证书状态
// 时间：2021-10-20
// 备注：无
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

    // 从控制台清空读取缓冲区
    while (ch != '\n')
    {
        ch = getchar();
    }

    return result;
}
