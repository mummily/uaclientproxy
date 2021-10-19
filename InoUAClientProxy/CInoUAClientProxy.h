#pragma once

#include "InoUAClientProxyExport.h"

enum class emFAServerType;
class CInoUAClientMgr;
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

protected:

private:
    CInoUAClientMgr* m_pUAClientMgr = nullptr;
};

