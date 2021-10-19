#pragma once

#include "InoUAClientProxyExport.h"

enum class emFAServerType;
class CInoUAClient;
class INO_EXPORT CInoUAClientMgr
{
public:
    CInoUAClientMgr(emFAServerType _emFAServerType);
    virtual ~CInoUAClientMgr();

public:
    // ��ȡ��UA�ͻ���
    CInoUAClient* getUAClient();

protected:

private:
    CInoUAClient* m_pUAClientMaster = nullptr;// ��UA�ͻ���
    CInoUAClient* m_pUAClientSlave = nullptr; // ��UA�ͻ���
};

