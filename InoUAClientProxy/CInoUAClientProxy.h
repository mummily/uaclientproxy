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
    // 连接客户端
    bool connect();
    // 是否连接客户端
    bool isconnect();

protected:

private:
    CInoUAClientMgr* m_pUAClientMgr = nullptr;
};

