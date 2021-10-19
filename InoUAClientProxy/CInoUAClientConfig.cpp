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
        printf("δ���������ļ���%s", sConfigurationFile.toUtf8());
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

    // ֤��������б�λ��
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

    // Ӧ������
    value = pSettings->value("ApplicationName", UaString());
    m_applicationName = value.toString();

    // ������ URL
    value = pSettings->value("DiscoveryURL", UaString("opc.tcp://localhost:48010"));
    m_discoveryUrl = value.toString();
    value = pSettings->value("ServerUrl", UaString("opc.tcp://localhost:48010"));
    m_serverUrl = value.toString();

    // Reconnection settings
    value = pSettings->value("AutomaticReconnect", UaVariant((OpcUa_Boolean)OpcUa_True));
    value.toBool(m_bAutomaticReconnect);
    value = pSettings->value("RetryInitialConnect", UaVariant((OpcUa_Boolean)OpcUa_False));
    value.toBool(m_bRetryInitialConnect);

    // ��ȡ�����ռ�����
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

    // ��ȡ NodeIds �����ڶ�ȡ
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

    // ��ȡ NodeIds���������ͺ�ֵ������д��
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
    pSettings->endGroup();  // NodesToWrite

    // ��ȡ NodeIds �����ڼ��
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

    // ��ȡ�������ڹ��˵� EventType �� NodeIds
    value = pSettings->value("EventTypeToFilter", UaString(""));
    m_eventTypeToFilter = UaNodeId::fromXmlString(value.toString());

    // ��ȡ NodeIds �Ե��÷���
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

    // ����Ŀ¼
    UaDir dirHelper("");
    UaUniString usClientCertificatePath(dirHelper.filePath(UaDir::fromNativeSeparators(m_clientCertificateFile.toUtf16())));
    dirHelper.mkpath(usClientCertificatePath);
    UaUniString usPrivateKeyPath(dirHelper.filePath(UaDir::fromNativeSeparators(m_clientPrivateKeyFile.toUtf16())));
    dirHelper.mkpath(usPrivateKeyPath);
    UaUniString usTrustListLocationPath(dirHelper.filePath(UaDir::fromNativeSeparators(m_certificateTrustListLocation.toUtf16())));
    dirHelper.mkpath(usTrustListLocationPath);
    UaUniString usRevocationListPath(dirHelper.filePath(UaDir::fromNativeSeparators(m_certificateRevocationListLocation.toUtf16())));
    dirHelper.mkpath(usRevocationListPath);

    // ���Լ��ؿͻ���֤��
    UaPkiCertificate clientCertificate = UaPkiCertificate::fromDERFile(m_clientCertificateFile);

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
        cert.toDERFile(m_clientCertificateFile.toUtf8());

        // ��˽Կ���浽�ļ�
        keyPair.toPEMFile(m_clientPrivateKeyFile.toUtf8(), 0);
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

    // ����ӳ���
    size = m_namespaceArray.length();
    UaInt16Array mappingTable;
    mappingTable.resize(size);

    // ���ӳ���
    for (i = 0; i < m_namespaceArray.length(); i++)
    {
        mappingTable[i] = (OpcUa_UInt16)i;
        // ���������ռ�uri
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

    // �滻 NodeIds �е������ռ�����
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

    // Ҫ���˵��¼�����
    m_eventTypeToFilter.setNamespaceIndex(mappingTable[m_eventTypeToFilter.namespaceIndex()]);

    // �����Ͷ���
    for (i = 0; i < m_methodsToCall.length(); i++)
    {
        m_methodsToCall[i].NamespaceIndex = mappingTable[m_methodsToCall[i].NamespaceIndex];
    }
    for (i = 0; i < m_objectToCall.length(); i++)
    {
        m_objectToCall[i].NamespaceIndex = mappingTable[m_objectToCall[i].NamespaceIndex];
    }

    // ���� namespace array
    m_namespaceArray = namespaceArray;
    return result;
}
