#pragma once

#include "InoExportDef.h"

// class UaStatus;
class CInoUAClient;
class CInoUAClientConfig;
class INO_EXPORT CInoUARedClient
{
public:
    CInoUARedClient();
    virtual ~CInoUARedClient();

public:
    // ���ӷ�����
    /*UaStatus*/bool connect();
    // �Ͽ���ͻ��˵�����
    /*UaStatus*/bool disconnect();
    // �Ƿ����ӷ�����
    bool isconnect();
    // ��ȡ��UA�ͻ���
    CInoUAClient* getUAClient();
    // ����������Ϣ
    void setConfiguration(CInoUAClientConfig* pConfigMaster, CInoUAClientConfig* pConfigSlave);
    // ��ȡ
    bool read();

protected:

private:
    CInoUAClient* m_pUAClientMaster = nullptr;// ��UA�ͻ���
    CInoUAClient* m_pUAClientSlave = nullptr; // ��UA�ͻ���
};

