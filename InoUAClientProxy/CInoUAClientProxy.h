#pragma once

#include "InoExportDef.h"

enum class emFAServerType;
class UaUniString;
class CInoUAClientMgr;
class CInoUAClientConfig;
class INO_EXPORT CInoUAClientProxy
{
public:
    CInoUAClientProxy(emFAServerType _emFAServerType);
    virtual ~CInoUAClientProxy();

    friend class CInoUAClientProxyMgr;

public:
    // ���ӿͻ���
    bool connect();
    // �Ƿ����ӿͻ���
    bool isconnect();
    // ��ȡ�ͻ�������
    UaUniString GetConfigPath();

protected:

private:
    CInoUAClientMgr* m_pUAClientMgr = nullptr; // �����ͻ��˹�����
    CInoUAClientConfig* m_pUAClientConfig = nullptr; //�����ͻ�������
    emFAServerType m_emFAServerType;
};

