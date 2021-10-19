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
    // 连接客户端
    bool connect();
    // 是否连接客户端
    bool isconnect();
    // 获取客户端配置
    UaUniString GetConfigPath();

protected:

private:
    CInoUAClientMgr* m_pUAClientMgr = nullptr; // 主备客户端管理器
    CInoUAClientConfig* m_pUAClientConfig = nullptr; //主备客户端配置
    emFAServerType m_emFAServerType;
};

