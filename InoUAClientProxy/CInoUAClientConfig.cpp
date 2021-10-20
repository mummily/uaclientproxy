#include "CInoUAClientConfig.h"
#include "uasettings.h"
#include "uadir.h"
#include "uapkicertificate.h"
#include "InoCommonDef.h"
#include "ScopeExit.h"

CInoUAClientConfig::CInoUAClientConfig()
{
}

CInoUAClientConfig::~CInoUAClientConfig()
{
}

// 描述：getServerUrl
// 时间：2021-10-20
// 备注：无
UaString CInoUAClientConfig::getServerUrl() const
{
    return m_serverUrl;
}

// 描述：getDiscoveryUrl
// 时间：2021-10-20
// 备注：无
UaString CInoUAClientConfig::getDiscoveryUrl() const
{
    return m_discoveryUrl;
}

// 描述：getApplicationName
// 时间：2021-10-20
// 备注：无
UaString CInoUAClientConfig::getApplicationName() const
{
    return m_applicationName;
}

// 描述：getAutomaticReconnect
// 时间：2021-10-20
// 备注：无
OpcUa_Boolean CInoUAClientConfig::getAutomaticReconnect() const
{
    return m_bAutomaticReconnect;
}

// 描述：getRetryInitialConnect
// 时间：2021-10-20
// 备注：无
OpcUa_Boolean CInoUAClientConfig::getRetryInitialConnect() const
{
    return m_bRetryInitialConnect;
}

// 描述：返回读取节点
// 时间：2021-10-20
// 备注：无
UaNodeIdArray CInoUAClientConfig::getNodesToRead() const
{
    return m_nodesToRead;
}

// 描述：返回写入节点
// 时间：2021-10-20
// 备注：无
UaNodeIdArray CInoUAClientConfig::getNodesToWrite() const
{
    return m_nodesToWrite;
}

// 描述：返回监视节点
// 时间：2021-10-20
// 备注：无
UaNodeIdArray CInoUAClientConfig::getNodesToMonitor() const
{
    return m_nodesToMonitor;
}

// 描述：返回写值
// 时间：2021-10-20
// 备注：无
UaVariantArray CInoUAClientConfig::getWriteValues() const
{
    return m_writeValues;
}

// 描述：返回事件类型过滤
// 时间：2021-10-20
// 备注：无
UaNodeId CInoUAClientConfig::getEventTypeToFilter() const
{
    return m_eventTypeToFilter;
}

// 描述：返回回调方法
// 时间：2021-10-20
// 备注：无
UaNodeIdArray CInoUAClientConfig::getMethodsToCall() const
{
    return m_methodsToCall;
}

// 描述：返回回调对象
// 时间：2021-10-20
// 备注：无
UaNodeIdArray CInoUAClientConfig::getObjectsToCall() const
{
    return m_objectToCall;
}

// 描述：加载客户端连接配置
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClientConfig::loadConfiguration(const UaString& sConfigurationFile)
{
    if (!UaDir("").exists(sConfigurationFile.toUtf8()))
    {
        printf("未发现配置文件：%s", sConfigurationFile.toUtf8());
        return OpcUa_BadInvalidArgument;
    }

    UaSettings* pSettings = new UaSettings(sConfigurationFile.toUtf16());
    SCOPE_EXIT(DelAndNil(pSettings););

    pSettings->beginGroup("InoClientConfig");
    SCOPE_EXIT(pSettings->endGroup(););

    // 获取值
    auto getValueAsString = [&](const UaUniString& sKey, const UaVariant& defaultValue = UaVariant())
        ->UaString
    {
        UaVariant value = pSettings->value("CertificateTrustListLocation", defaultValue);
        return value.toString();
    };
    auto getValueAsBool = [&](const UaUniString& sKey, const UaVariant& defaultValue = UaVariant())
        ->OpcUa_Boolean
    {
        UaVariant value = pSettings->value("CertificateTrustListLocation", defaultValue);
        OpcUa_Boolean bVal;
        OpcUa_StatusCode status = value.toBool(bVal);
        assert(OpcUa_IsGood(status));
        return bVal;
    };
    auto getValueAsU32 = [&](const UaUniString& sKey, const UaVariant& defaultValue = UaVariant())
        ->OpcUa_UInt32
    {
        UaVariant value = pSettings->value("CertificateTrustListLocation", defaultValue);
        OpcUa_UInt32 u32Val;
        OpcUa_StatusCode status = value.toUInt32(u32Val);
        assert(OpcUa_IsGood(status));
        return u32Val;
    };
    auto getValueAsByte = [&](const UaUniString& sKey, const UaVariant& defaultValue = UaVariant())
        ->OpcUa_Byte
    {
        UaVariant value = pSettings->value("CertificateTrustListLocation", defaultValue);
        OpcUa_Byte byteVal;
        OpcUa_StatusCode status = value.toByte(byteVal);
        assert(OpcUa_IsGood(status));
        return byteVal;
    };
    auto readNodeGroup = [&](UaNodeIdArray& nodeArray, const UaUniString& sGroup, const UaString& sNode)
    {
        nodeArray.clear();

        pSettings->beginGroup(sGroup);
        SCOPE_EXIT(pSettings->endGroup(););

        OpcUa_UInt32 size = getValueAsU32("size", (OpcUa_UInt32)0);
        nodeArray.resize(size);
        for (OpcUa_UInt32 i = 0; i < size; i++)
        {
            UaString sTempKey = UaString("%0%1").arg(sNode).arg((int)i);
            UaString value = getValueAsString(sTempKey.toUtf16(), UaString(""));
            UaNodeId::fromXmlString(value).copyTo(&nodeArray[i]);
        }
    };
    auto readStringGroup = [&](UaStringArray& nodeArray, const UaUniString& sGroup, const UaString& sNode)
    {
        nodeArray.clear();

        pSettings->beginGroup(sGroup);
        SCOPE_EXIT(pSettings->endGroup(););

        OpcUa_UInt32 size = getValueAsU32("size", (OpcUa_UInt32)0);
        nodeArray.resize(size);
        for (OpcUa_UInt32 i = 0; i < size; i++)
        {
            UaString sTempKey = UaString("%0%1").arg(sNode).arg((int)i);
            UaString value = getValueAsString(sTempKey.toUtf16(), UaString(""));
            value.copyTo(&nodeArray[i]);
        }
    };

    // 证书和信任列表位置
    m_certificateTrustListLocation = getValueAsString("CertificateTrustListLocation");
    m_certificateRevocationListLocation = getValueAsString("CertificateRevocationListLocation");
    m_issuersCertificatesLocation = getValueAsString("IssuersCertificatesLocation");
    m_issuersRevocationListLocation = getValueAsString("IssuersRevocationListLocation");
    m_clientCertificate = getValueAsString("ClientCertificate");
    m_clientPrivateKey = getValueAsString("ClientPrivateKey");

    // 应用名称
    m_applicationName = getValueAsString("ApplicationName", UaString());

    // 服务器 URL
    m_discoveryUrl = getValueAsString("DiscoveryURL", UaString("opc.tcp://localhost:48010"));
    m_serverUrl = getValueAsString("ServerUrl", UaString("opc.tcp://localhost:48010"));

    // 重连设置
    m_bAutomaticReconnect = getValueAsBool("AutomaticReconnect", UaVariant((OpcUa_Boolean)OpcUa_True));
    m_bRetryInitialConnect = getValueAsBool("RetryInitialConnect", UaVariant((OpcUa_Boolean)OpcUa_False));

    // 读取 EventTypeToFilter --> 事件过滤：m_eventTypeToFilter
    m_eventTypeToFilter = UaNodeId::fromXmlString(getValueAsString("EventTypeToFilter", UaString("")));

    // 读取 NSArray 命名空间数组 --> m_namespaceArray
    readStringGroup(m_namespaceArray, "NSArray", "NameSpaceUri0");

    // 读取 NodesToRead --> 读取的变量：m_nodesToRead
    readNodeGroup(m_nodesToRead, "NodesToRead", "Variable0");

    // 读取 NodesToWrite --> 写入的变量：m_nodesToWrite 写入的变量的值：m_writeValues
    {
        readNodeGroup(m_nodesToWrite, "NodesToWrite", "Variable0");

        pSettings->beginGroup("NodesToWrite");
        SCOPE_EXIT(pSettings->endGroup(););

        OpcUa_UInt32 size = getValueAsU32("size", (OpcUa_UInt32)0);

        // DataTypes
        UaByteArray writeDataTypes;
        writeDataTypes.resize(size);
        for (OpcUa_UInt32 i = 0; i < size; i++)
        {
            UaString sTempKey = UaString("DataType0%1").arg((int)i);
            writeDataTypes[(int)i] = getValueAsByte(sTempKey.toUtf16(), UaString(""));
        }

        // Values
        m_writeValues.clear();
        m_writeValues.resize(size);
        for (OpcUa_UInt32 i = 0; i < size; i++)
        {
            UaString sTempKey = UaString("Value0%1").arg((int)i);
            UaVariant value = pSettings->value(sTempKey.toUtf16());
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
    }

    // 读取 NodesToMonitor --> 监视的变量：m_nodesToMonitor
    readNodeGroup(m_nodesToMonitor, "NodesToMonitor", "Variable0");

    // 读取 MethodsToCall --> 方法：m_methodsToCall
    readNodeGroup(m_methodsToCall, "MethodsToCall", "Method0");
    // 读取 MethodsToCall --> 对象：m_objectToCall
    readNodeGroup(m_objectToCall, "MethodsToCall", "Object0");

    UaStatus result;
    return result;
}

// 描述：安装安全证书
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClientConfig::setupSecurity(SessionSecurityInfo& sessionSecurityInfo)
{
    UaStatus result;

    // 创建目录
    UaDir dirHelper("");
    UaUniString usClientCertificate(dirHelper.filePath(UaDir::fromNativeSeparators(m_clientCertificate.toUtf16())));
    dirHelper.mkpath(usClientCertificate);
    UaUniString usClientPrivateKey(dirHelper.filePath(UaDir::fromNativeSeparators(m_clientPrivateKey.toUtf16())));
    dirHelper.mkpath(usClientPrivateKey);
    UaUniString usCertificateTrustListLocation(dirHelper.filePath(UaDir::fromNativeSeparators(m_certificateTrustListLocation.toUtf16())));
    dirHelper.mkpath(usCertificateTrustListLocation);
    UaUniString usCertificateRevocationListLocation(dirHelper.filePath(UaDir::fromNativeSeparators(m_certificateRevocationListLocation.toUtf16())));
    dirHelper.mkpath(usCertificateRevocationListLocation);

    // 尝试加载客户端证书
    UaPkiCertificate clientCertificate = UaPkiCertificate::fromDERFile(m_clientCertificate);

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
        cert.toDERFile(m_clientCertificate.toUtf8());

        // 将私钥保存到文件
        keyPair.toPEMFile(m_clientPrivateKey.toUtf8(), 0);
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
        m_clientCertificate,
        m_clientPrivateKey);
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

// 描述：更新命令空间索引
// 时间：2021-10-20
// 备注：无
UaStatus CInoUAClientConfig::updateNamespaceIndexes(const UaStringArray& namespaceArray)
{
    // 创建映射表
    UaInt16Array mappingTable;
    mappingTable.resize(m_namespaceArray.length());

    // 填充映射表，找到新ns下的index值
    for (OpcUa_UInt32 i = 0; i < m_namespaceArray.length(); i++)
    {
        mappingTable[i] = (OpcUa_UInt16)i;
        // 查找命名空间uri
        for (OpcUa_UInt32 j = 0; j < namespaceArray.length(); j++)
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

    // 替换 NodesToRead 中的命名空间索引
    for (OpcUa_UInt32 i = 0; i < m_nodesToRead.length(); i++)
    {
        m_nodesToRead[i].NamespaceIndex = mappingTable[m_nodesToRead[i].NamespaceIndex];
    }
    // 替换 NodeToWrite 中的命名空间索引
    for (OpcUa_UInt32 i = 0; i < m_nodesToWrite.length(); i++)
    {
        m_nodesToWrite[i].NamespaceIndex = mappingTable[m_nodesToWrite[i].NamespaceIndex];
    }
    // 替换 NodesToMonitor 中的命名空间索引
    for (OpcUa_UInt32 i = 0; i < m_nodesToMonitor.length(); i++)
    {
        m_nodesToMonitor[i].NamespaceIndex = mappingTable[m_nodesToMonitor[i].NamespaceIndex];
    }

    // 替换 要过滤的事件类型 中的命名空间索引
    m_eventTypeToFilter.setNamespaceIndex(mappingTable[m_eventTypeToFilter.namespaceIndex()]);

    // 替换 方法和对象 中的命名空间索引
    for (OpcUa_UInt32 i = 0; i < m_methodsToCall.length(); i++)
    {
        m_methodsToCall[i].NamespaceIndex = mappingTable[m_methodsToCall[i].NamespaceIndex];
    }
    for (OpcUa_UInt32 i = 0; i < m_objectToCall.length(); i++)
    {
        m_objectToCall[i].NamespaceIndex = mappingTable[m_objectToCall[i].NamespaceIndex];
    }

    // 更新命名空间
    m_namespaceArray = namespaceArray;

    return OpcUa_Good;
}
