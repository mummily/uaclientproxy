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

// ������getServerUrl
// ʱ�䣺2021-10-20
// ��ע����
UaString CInoUAClientConfig::getServerUrl() const
{
    return m_serverUrl;
}

// ������getDiscoveryUrl
// ʱ�䣺2021-10-20
// ��ע����
UaString CInoUAClientConfig::getDiscoveryUrl() const
{
    return m_discoveryUrl;
}

// ������getApplicationName
// ʱ�䣺2021-10-20
// ��ע����
UaString CInoUAClientConfig::getApplicationName() const
{
    return m_applicationName;
}

// ������getAutomaticReconnect
// ʱ�䣺2021-10-20
// ��ע����
OpcUa_Boolean CInoUAClientConfig::getAutomaticReconnect() const
{
    return m_bAutomaticReconnect;
}

// ������getRetryInitialConnect
// ʱ�䣺2021-10-20
// ��ע����
OpcUa_Boolean CInoUAClientConfig::getRetryInitialConnect() const
{
    return m_bRetryInitialConnect;
}

// ���������ض�ȡ�ڵ�
// ʱ�䣺2021-10-20
// ��ע����
UaNodeIdArray CInoUAClientConfig::getNodesToRead() const
{
    return m_nodesToRead;
}

// ����������д��ڵ�
// ʱ�䣺2021-10-20
// ��ע����
UaNodeIdArray CInoUAClientConfig::getNodesToWrite() const
{
    return m_nodesToWrite;
}

// ���������ؼ��ӽڵ�
// ʱ�䣺2021-10-20
// ��ע����
UaNodeIdArray CInoUAClientConfig::getNodesToMonitor() const
{
    return m_nodesToMonitor;
}

// ����������дֵ
// ʱ�䣺2021-10-20
// ��ע����
UaVariantArray CInoUAClientConfig::getWriteValues() const
{
    return m_writeValues;
}

// �����������¼����͹���
// ʱ�䣺2021-10-20
// ��ע����
UaNodeId CInoUAClientConfig::getEventTypeToFilter() const
{
    return m_eventTypeToFilter;
}

// ���������ػص�����
// ʱ�䣺2021-10-20
// ��ע����
UaNodeIdArray CInoUAClientConfig::getMethodsToCall() const
{
    return m_methodsToCall;
}

// ���������ػص�����
// ʱ�䣺2021-10-20
// ��ע����
UaNodeIdArray CInoUAClientConfig::getObjectsToCall() const
{
    return m_objectToCall;
}

// ���������ؿͻ�����������
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClientConfig::loadConfiguration(const UaString& sConfigurationFile)
{
    if (!UaDir("").exists(sConfigurationFile.toUtf8()))
    {
        printf("δ���������ļ���%s", sConfigurationFile.toUtf8());
        return OpcUa_BadInvalidArgument;
    }

    UaSettings* pSettings = new UaSettings(sConfigurationFile.toUtf16());
    SCOPE_EXIT(DelAndNil(pSettings););

    pSettings->beginGroup("InoClientConfig");
    SCOPE_EXIT(pSettings->endGroup(););

    // ��ȡֵ
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

    // ֤��������б�λ��
    m_certificateTrustListLocation = getValueAsString("CertificateTrustListLocation");
    m_certificateRevocationListLocation = getValueAsString("CertificateRevocationListLocation");
    m_issuersCertificatesLocation = getValueAsString("IssuersCertificatesLocation");
    m_issuersRevocationListLocation = getValueAsString("IssuersRevocationListLocation");
    m_clientCertificate = getValueAsString("ClientCertificate");
    m_clientPrivateKey = getValueAsString("ClientPrivateKey");

    // Ӧ������
    m_applicationName = getValueAsString("ApplicationName", UaString());

    // ������ URL
    m_discoveryUrl = getValueAsString("DiscoveryURL", UaString("opc.tcp://localhost:48010"));
    m_serverUrl = getValueAsString("ServerUrl", UaString("opc.tcp://localhost:48010"));

    // ��������
    m_bAutomaticReconnect = getValueAsBool("AutomaticReconnect", UaVariant((OpcUa_Boolean)OpcUa_True));
    m_bRetryInitialConnect = getValueAsBool("RetryInitialConnect", UaVariant((OpcUa_Boolean)OpcUa_False));

    // ��ȡ EventTypeToFilter --> �¼����ˣ�m_eventTypeToFilter
    m_eventTypeToFilter = UaNodeId::fromXmlString(getValueAsString("EventTypeToFilter", UaString("")));

    // ��ȡ NSArray �����ռ����� --> m_namespaceArray
    readStringGroup(m_namespaceArray, "NSArray", "NameSpaceUri0");

    // ��ȡ NodesToRead --> ��ȡ�ı�����m_nodesToRead
    readNodeGroup(m_nodesToRead, "NodesToRead", "Variable0");

    // ��ȡ NodesToWrite --> д��ı�����m_nodesToWrite д��ı�����ֵ��m_writeValues
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
            // ��ֵת��Ϊ��ȷ������
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

    // ��ȡ NodesToMonitor --> ���ӵı�����m_nodesToMonitor
    readNodeGroup(m_nodesToMonitor, "NodesToMonitor", "Variable0");

    // ��ȡ MethodsToCall --> ������m_methodsToCall
    readNodeGroup(m_methodsToCall, "MethodsToCall", "Method0");
    // ��ȡ MethodsToCall --> ����m_objectToCall
    readNodeGroup(m_objectToCall, "MethodsToCall", "Object0");

    UaStatus result;
    return result;
}

// ��������װ��ȫ֤��
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClientConfig::setupSecurity(SessionSecurityInfo& sessionSecurityInfo)
{
    UaStatus result;

    // ����Ŀ¼
    UaDir dirHelper("");
    UaUniString usClientCertificate(dirHelper.filePath(UaDir::fromNativeSeparators(m_clientCertificate.toUtf16())));
    dirHelper.mkpath(usClientCertificate);
    UaUniString usClientPrivateKey(dirHelper.filePath(UaDir::fromNativeSeparators(m_clientPrivateKey.toUtf16())));
    dirHelper.mkpath(usClientPrivateKey);
    UaUniString usCertificateTrustListLocation(dirHelper.filePath(UaDir::fromNativeSeparators(m_certificateTrustListLocation.toUtf16())));
    dirHelper.mkpath(usCertificateTrustListLocation);
    UaUniString usCertificateRevocationListLocation(dirHelper.filePath(UaDir::fromNativeSeparators(m_certificateRevocationListLocation.toUtf16())));
    dirHelper.mkpath(usCertificateRevocationListLocation);

    // ���Լ��ؿͻ���֤��
    UaPkiCertificate clientCertificate = UaPkiCertificate::fromDERFile(m_clientCertificate);

    // ֤�鲻���� - ���Ǵ���һ���µ�
    if (clientCertificate.isNull())
    {
        // ����֤��
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

        // ������ǩ��֤��
        UaPkiCertificate cert(info, identity, keyPair);

        // ����Կ���浽�ļ�
        cert.toDERFile(m_clientCertificate.toUtf8());

        // ��˽Կ���浽�ļ�
        keyPair.toPEMFile(m_clientPrivateKey.toUtf8(), 0);
    }

    // ��ʼ�� PKI �ṩ������ʹ�� OpenSSL
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

    // ���ؿͻ���֤���˽Կ
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

// ��������������ռ�����
// ʱ�䣺2021-10-20
// ��ע����
UaStatus CInoUAClientConfig::updateNamespaceIndexes(const UaStringArray& namespaceArray)
{
    // ����ӳ���
    UaInt16Array mappingTable;
    mappingTable.resize(m_namespaceArray.length());

    // ���ӳ����ҵ���ns�µ�indexֵ
    for (OpcUa_UInt32 i = 0; i < m_namespaceArray.length(); i++)
    {
        mappingTable[i] = (OpcUa_UInt16)i;
        // ���������ռ�uri
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

    // �滻 NodesToRead �е������ռ�����
    for (OpcUa_UInt32 i = 0; i < m_nodesToRead.length(); i++)
    {
        m_nodesToRead[i].NamespaceIndex = mappingTable[m_nodesToRead[i].NamespaceIndex];
    }
    // �滻 NodeToWrite �е������ռ�����
    for (OpcUa_UInt32 i = 0; i < m_nodesToWrite.length(); i++)
    {
        m_nodesToWrite[i].NamespaceIndex = mappingTable[m_nodesToWrite[i].NamespaceIndex];
    }
    // �滻 NodesToMonitor �е������ռ�����
    for (OpcUa_UInt32 i = 0; i < m_nodesToMonitor.length(); i++)
    {
        m_nodesToMonitor[i].NamespaceIndex = mappingTable[m_nodesToMonitor[i].NamespaceIndex];
    }

    // �滻 Ҫ���˵��¼����� �е������ռ�����
    m_eventTypeToFilter.setNamespaceIndex(mappingTable[m_eventTypeToFilter.namespaceIndex()]);

    // �滻 �����Ͷ��� �е������ռ�����
    for (OpcUa_UInt32 i = 0; i < m_methodsToCall.length(); i++)
    {
        m_methodsToCall[i].NamespaceIndex = mappingTable[m_methodsToCall[i].NamespaceIndex];
    }
    for (OpcUa_UInt32 i = 0; i < m_objectToCall.length(); i++)
    {
        m_objectToCall[i].NamespaceIndex = mappingTable[m_objectToCall[i].NamespaceIndex];
    }

    // ���������ռ�
    m_namespaceArray = namespaceArray;

    return OpcUa_Good;
}
