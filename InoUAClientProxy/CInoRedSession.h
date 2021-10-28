#pragma once

#include "InoExportDef.h"

class UaStatus;
class CInoSession;
class CInoSessionConfig;
class INO_EXPORT CInoRedSession
{
public:
    CInoRedSession();
    virtual ~CInoRedSession();

public:
    // ���ӷ�����
    UaStatus connect();
    // �Ͽ���ͻ��˵�����
    UaStatus disconnect();
    // ��ȡ��UA�ͻ���
    CInoSession* getSession();
    // ����������Ϣ
    void setConfiguration(CInoSessionConfig* pConfigMaster, CInoSessionConfig* pConfigSlave);
    // ��ȡ
    bool read();

protected:

private:
    CInoSession* m_pSessionMaster = nullptr;// ��UA�ͻ���
    CInoSession* m_pSessionSlave = nullptr; // ��UA�ͻ���
};

