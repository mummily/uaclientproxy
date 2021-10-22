#pragma once

#include "InoExportDef.h"

enum class emFAServerType;
class UaUniString;
class CInoUAClientMgr;
class CInoUAClientConfig;
class INO_EXPORT CInoUAClientConnect
{
public:
    CInoUAClientConnect(emFAServerType serverType);
    virtual ~CInoUAClientConnect();

    friend class CInoUAClientProxyMgr;

public:
    // ���ӿͻ���
    bool connect();
    // �Ͽ���ͻ��˵�����
    bool disconnect();
    // �Ƿ����ӿͻ���
    bool isconnect();

    // Get/Set
    CInoUAClientMgr* GetUAClientMgr() const { return m_pUAClientMgr; }
    void SetUAClientMgr(CInoUAClientMgr* pUAClientMgr) { m_pUAClientMgr = pUAClientMgr; }

protected:
private:
    // ��ȡ�ͻ�������
    UaUniString GetConfigPath();

private:
    CInoUAClientMgr* m_pUAClientMgr = nullptr; // �����ͻ��˹�����
    CInoUAClientConfig* m_pUAClientConfig = nullptr; //�����ͻ�������
    emFAServerType m_emFAServerType; // FA����������
};

