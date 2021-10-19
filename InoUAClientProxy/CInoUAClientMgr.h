#pragma once

#include "InoExportDef.h"

class UaStatus;
class CInoUAClient;
class CInoUAClientConfig;
class INO_EXPORT CInoUAClientMgr
{
public:
    CInoUAClientMgr();
    virtual ~CInoUAClientMgr();

public:
    // ���ӷ�����
    UaStatus connect();
    // ��ȡ��UA�ͻ���
    CInoUAClient* getUAClient();
    // ����������Ϣ
    void setConfiguration(CInoUAClientConfig* pConfiguration);
    // ��ȡ������Ϣ
    CInoUAClientConfig* getConfiguration();

protected:

private:
    CInoUAClient* m_pUAClientMaster = nullptr;// ��UA�ͻ���
    CInoUAClient* m_pUAClientSlave = nullptr; // ��UA�ͻ���
};

