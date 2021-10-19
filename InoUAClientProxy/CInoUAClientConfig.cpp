#include "CInoUAClientConfig.h"
#include "uasettings.h"
#include "uadir.h"
#include "uapkicertificate.h"
#include "InoCommonDef.h"

CInoUAClientConfig::CInoUAClientConfig()
{
}

CInoUAClientConfig::~CInoUAClientConfig()
{
}

UaString CInoUAClientConfig::getServerUrl() const
{
    return m_serverUrl;
}

UaString CInoUAClientConfig::getDiscoveryUrl() const
{
    return m_discoveryUrl;
}

UaString CInoUAClientConfig::getApplicationName() const
{
    return m_applicationName;
}

OpcUa_Boolean CInoUAClientConfig::getAutomaticReconnect() const
{
    return m_bAutomaticReconnect;
}

OpcUa_Boolean CInoUAClientConfig::getRetryInitialConnect() const
{
    return m_bRetryInitialConnect;
}

UaNodeIdArray CInoUAClientConfig::getNodesToRead() const
{
    return m_nodesToRead;
}

UaNodeIdArray CInoUAClientConfig::getNodesToWrite() const
{
    return m_nodesToWrite;
}

UaNodeIdArray CInoUAClientConfig::getNodesToMonitor() const
{
    return m_nodesToMonitor;
}

UaVariantArray CInoUAClientConfig::getWriteValues() const
{
    return m_writeValues;
}

UaNodeId CInoUAClientConfig::getEventTypeToFilter() const
{
    return m_eventTypeToFilter;
}

UaNodeIdArray CInoUAClientConfig::getMethodsToCall() const
{
    return m_methodsToCall;
}

UaNodeIdArray CInoUAClientConfig::getObjectsToCall() const
{
    return m_objectToCall;
}

UaStatus CInoUAClientConfig::loadConfiguration(const UaString& sConfigurationFile)
{
    if (!UaDir("").exists(sConfigurationFile.toUtf8()))
    {
        printf("未发现配置文件：%s", sConfigurationFile.toUtf8());
        return OpcUa_BadInvalidArgument;
    }

    UaStatus result;
    UaVariant value;
    UaString sTempKey;
    OpcUa_UInt32 i = 0;
    OpcUa_UInt32 size = 0;
    OpcUa_Byte byteVal;
    UaSettings* pSettings = nullptr;
    pSettings = new UaSettings(sConfigurationFile.toUtf16());

    pSettings->beginGroup("InoClientConfig");

    // 证书和信任列表位置
    value = pSettings->value("CertificateTrustListLocation");
    m_certificateTrustListLocation = value.toString();
    value = pSettings->value("CertificateRevocationListLocation");
    m_certificateRevocationListLocation = value.toString();
    value = pSettings->value("IssuersCertificatesLocation");
    m_issuersCertificatesLocation = value.toString();
    value = pSettings->value("IssuersRevocationListLocation");
    m_issuersRevocationListLocation = value.toString();
    value = pSettings->value("ClientCertificate");
    m_clientCertificateFile = value.toString();
    value = pSettings->value("ClientPrivateKey");
    m_clientPrivateKeyFile = value.toString();

    // 应用名称
    value = pSettings->value("ApplicationName", UaString());
    m_applicationName = value.toString();

    // 服务器 URL
    value = pSettings->value("DiscoveryURL", UaString("opc.tcp://localhost:48010"));
    m_discoveryUrl = value.toString();
    value = pSettings->value("ServerUrl", UaString("opc.tcp://localhost:48010"));
    m_serverUrl = value.toString();

    // Reconnection settings
    value = pSettings->value("AutomaticReconnect", UaVariant((OpcUa_Boolean)OpcUa_True));
    value.toBool(m_bAutomaticReconnect);
    value = pSettings->value("RetryInitialConnect", UaVariant((OpcUa_Boolean)OpcUa_False));
    value.toBool(m_bRetryInitialConnect);

    // 读取命名空间数组
    m_namespaceArray.clear();
    pSettings->beginGroup("NSArray");
    value = pSettings->value("size", (OpcUa_UInt32)0);
    value.toUInt32(size);
    m_namespaceArray.resize(size);
    for (i = 0; i < size; i++)
    {
        sTempKey = UaString("NameSpaceUri0%1").arg((int)i);
        value = pSettings->value(sTempKey.toUtf16(), UaString(""));
        value.toString().copyTo(&m_namespaceArray[i]);
    }
    pSettings->endGroup();  // NSArray

    // 读取 NodeIds 以用于读取
    m_nodesToRead.clear();
    pSettings->beginGroup("NodesToRead");
    value = pSettings->value("size", (OpcUa_UInt32)0);
    value.toUInt32(size);
    m_nodesToRead.resize(size);
    for (i = 0; i < size; i++)
    {
        sTempKey = UaString("Variable0%1").arg((int)i);
        value = pSettings->value(sTempKey.toUtf16(), UaString(""));
        UaNodeId::fromXmlString(value.toString()).copyTo(&m_nodesToRead[i]);
    }
    pSettings->endGroup();  // NodesToRead

    // 读取 NodeIds、数据类型和值以用于写入
    m_nodesToWrite.clear();
    pSettings->beginGroup("NodesToWrite");
    value = pSettings->value("size", (OpcUa_UInt32)0);
    value.toUInt32(size);
    // NodeIds
    m_nodesToWrite.resize(size);
    for (i = 0; i < size; i++)
    {
        sTempKey = UaString("Variable0%1").arg((int)i);
        value = pSettings->value(sTempKey.toUtf16(), UaString(""));
        UaNodeId::fromXmlString(value.toString()).copyTo(&m_nodesToWrite[i]);
    }
    // DataTypes
    UaByteArray writeDataTypes;
    writeDataTypes.resize(size);
    for (i = 0; i < size; i++)
    {
        sTempKey = UaString("DataType0%1").arg((int)i);
        value = pSettings->value(sTempKey.toUtf16(), UaString(""));
        value.toByte(byteVal);
        writeDataTypes[(int)i] = byteVal;
    }
    // Values
    m_writeValues.resize(size);
    for (i = 0; i < size; i++)
    {
        sTempKey = UaString("Value0%1").arg((int)i);
        value = pSettings->value(sTempKey.toUtf16());
        // 将值转换为正确的类型
        OpcUa_BuiltInType type = (OpcUa_BuiltInType)(char)writeDataTypes[(int)i];
        if (OpcUa_IsGood(value.changeType(type, OpcUa_False)))
        {
            value.copyTo(&m_writeValues[i]);
        }
        else
        {
            printf("Cannot convert variant value: %s\n", value.toString().toUtf8());
        }
    }
    pSettings->endGroup();  // NodesToWrite

    // 读取 NodeIds 以用于监控
    m_nodesToMonitor.clear();
    pSettings->beginGroup("NodesToMonitor");
    value = pSettings->value("size", (OpcUa_UInt32)0);
    value.toUInt32(size);
    m_nodesToMonitor.resize(size);
    for (i = 0; i < size; i++)
    {
        sTempKey = UaString("Variable0%1").arg((int)i);
        value = pSettings->value(sTempKey.toUtf16(), UaString(""));
        UaNodeId::fromXmlString(value.toString()).copyTo(&m_nodesToMonitor[i]);
    }
    pSettings->endGroup();  // NodesToMonitor

    // 读取我们用于过滤的 EventType 的 NodeIds
    value = pSettings->value("EventTypeToFilter", UaString(""));
    m_eventTypeToFilter = UaNodeId::fromXmlString(value.toString());

    // 读取 NodeIds 以调用方法
    m_methodsToCall.clear();
    m_objectToCall.clear();
    pSettings->beginGroup("MethodsToCall");
    value = pSettings->value("size", (OpcUa_UInt32)0);
    value.toUInt32(size);
    m_methodsToCall.resize(size);
    m_objectToCall.resize(size);
    for (i = 0; i < size; i++)
    {
        sTempKey = UaString("Method0%1").arg((int)i);
        value = pSettings->value(sTempKey.toUtf16(), UaString(""));
        UaNodeId::fromXmlString(value.toString()).copyTo(&m_methodsToCall[i]);

        sTempKey = UaString("Object0%1").arg((int)i);
        value = pSettings->value(sTempKey.toUtf16(), UaString(""));
        UaNodeId::fromXmlString(value.toString()).copyTo(&m_objectToCall[i]);
    }
    pSettings->endGroup();  // MethodsToCall

    pSettings->endGroup(); // UaClientConfig

    DelAndNil(pSettings);

    return result;
}

UaStatus CInoUAClientConfig::setupSecurity(SessionSecurityInfo& sessionSecurityInfo)
{
    UaStatus result;

    // 创建目录
    UaDir dirHelper("");
    UaUniString usClientCertificatePath(dirHelper.filePath(UaDir::fromNativeSeparators(m_clientCertificateFile.toUtf16())));
    dirHelper.mkpath(usClientCertificatePath);
    UaUniString usPrivateKeyPath(dirHelper.filePath(UaDir::fromNativeSeparators(m_clientPrivateKeyFile.toUtf16())));
    dirHelper.mkpath(usPrivateKeyPath);
    UaUniString usTrustListLocationPath(dirHelper.filePath(UaDir::fromNativeSeparators(m_certificateTrustListLocation.toUtf16())));
    dirHelper.mkpath(usTrustListLocationPath);
    UaUniString usRevocationListPath(dirHelper.filePath(UaDir::fromNativeSeparators(m_certificateRevocationListLocation.toUtf16())));
    dirHelper.mkpath(usRevocationListPath);

    // 尝试加载客户端证书
    UaPkiCertificate clientCertificate = UaPkiCertificate::fromDERFile(m_clientCertificateFile);

    // 证书不存在 - 我们创建一个新的
    if (clientCertificate.isNull())
    {
        // 创建证书
        UaPkiRsaKeyPair keyPair(1024);
        UaPkiIdentity   identity;

        UaString sNodeName;
        char szHostName[256];
        if (0 == UA_GetHostname(szHostName, 256))
        {
            sNodeName = szHostName;
        }

        identity.commonName = UaString("Client_Cpp_SDK@%1").arg(sNodeName);
        identity.organization = "Organization";
        identity.organizationUnit = "Unit";
        identity.locality = "LocationName";
        identity.state = "State";
        identity.country = "DE";
        identity.domainComponent = sNodeName;

        UaPkiCertificateInfo info;
        info.URI = UaString("urn:%1:%2:%3").arg(sNodeName).arg(COMPANY_NAME).arg(PRODUCT_NAME);
        info.DNSNames.create(1);
        sNodeName.copyTo(&info.DNSNames[0]);
        info.validTime = 3600 * 24 * 365 * 5; // 5 years in seconds

        // 创建自签名证书
        UaPkiCertificate cert(info, identity, keyPair);

        // 将公钥保存到文件
        cert.toDERFile(m_clientCertificateFile.toUtf8());

        // 将私钥保存到文件
        keyPair.toPEMFile(m_clientPrivateKeyFile.toUtf8(), 0);
    }

    // 初始化 PKI 提供程序以使用 OpenSSL
    result = sessionSecurityInfo.initializePkiProviderOpenSSL(
        m_certificateRevocationListLocation,
        m_certificateTrustListLocation,
        m_issuersRevocationListLocation,
        m_issuersCertificatesLocation);
    if (result.isBad())
    {
        printf("*******************************************************\n");
        printf("** setupSecurity failed!\n");
        printf("** Could not initialize PKI\n");
        printf("*******************************************************\n");
        return result;
    }

    // 加载客户端证书和私钥
    result = sessionSecurityInfo.loadClientCertificateOpenSSL(
        m_clientCertificateFile,
        m_clientPrivateKeyFile);
    if (result.isBad())
    {
        printf("*******************************************************\n");
        printf("** setupSecurity failed!\n");
        printf("** Could not load Client certificate\n");
        printf("** Connect will work only without security\n");
        printf("*******************************************************\n");
        return result;
    }

    return result;
}

UaStatus CInoUAClientConfig::updateNamespaceIndexes(const UaStringArray& namespaceArray)
{
    UaStatus result;
    OpcUa_UInt32 i, j;
    OpcUa_UInt32 size;

    // 创建映射表
    size = m_namespaceArray.length();
    UaInt16Array mappingTable;
    mappingTable.resize(size);

    // 填充映射表
    for (i = 0; i < m_namespaceArray.length(); i++)
    {
        mappingTable[i] = (OpcUa_UInt16)i;
        // 查找命名空间uri
        for (j = 0; j < namespaceArray.length(); j++)
        {
            UaString string1(m_namespaceArray[i]);
            UaString string2(namespaceArray[j]);
            if (string1 == string2)
            {
                mappingTable[i] = (OpcUa_UInt16)j;
                break;
            }
        }
    }

    // 替换 NodeIds 中的命名空间索引
    // NodesToRead
    for (i = 0; i < m_nodesToRead.length(); i++)
    {
        m_nodesToRead[i].NamespaceIndex = mappingTable[m_nodesToRead[i].NamespaceIndex];
    }
    // NodeToWrite
    for (i = 0; i < m_nodesToWrite.length(); i++)
    {
        m_nodesToWrite[i].NamespaceIndex = mappingTable[m_nodesToWrite[i].NamespaceIndex];
    }
    // NodesToMonitor
    for (i = 0; i < m_nodesToMonitor.length(); i++)
    {
        m_nodesToMonitor[i].NamespaceIndex = mappingTable[m_nodesToMonitor[i].NamespaceIndex];
    }

    // 要过滤的事件类型
    m_eventTypeToFilter.setNamespaceIndex(mappingTable[m_eventTypeToFilter.namespaceIndex()]);

    // 方法和对象
    for (i = 0; i < m_methodsToCall.length(); i++)
    {
        m_methodsToCall[i].NamespaceIndex = mappingTable[m_methodsToCall[i].NamespaceIndex];
    }
    for (i = 0; i < m_objectToCall.length(); i++)
    {
        m_objectToCall[i].NamespaceIndex = mappingTable[m_objectToCall[i].NamespaceIndex];
    }

    // 更新 namespace array
    m_namespaceArray = namespaceArray;
    return result;
}
