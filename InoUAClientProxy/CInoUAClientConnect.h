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
    // 连接客户端
    bool connect();
    // 断开与客户端的连接
    bool disconnect();
    // 是否连接客户端
    bool isconnect();

    // Get/Set
    CInoUAClientMgr* GetUAClientMgr() const { return m_pUAClientMgr; }
    void SetUAClientMgr(CInoUAClientMgr* pUAClientMgr) { m_pUAClientMgr = pUAClientMgr; }

protected:
private:
    // 获取客户端配置
    UaUniString GetConfigPath();

private:
    CInoUAClientMgr* m_pUAClientMgr = nullptr; // 主备客户端管理器
    CInoUAClientConfig* m_pUAClientConfig = nullptr; //主备客户端配置
    emFAServerType m_emFAServerType; // FA服务器类型
};

