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
    // 连接服务器
    UaStatus connect();
    // 断开与客户端的连接
    UaStatus disconnect();
    // 获取主UA客户端
    CInoSession* getSession();
    // 设置配置信息
    void setConfiguration(CInoSessionConfig* pConfigMaster, CInoSessionConfig* pConfigSlave);
    // 读取
    bool read();

protected:

private:
    CInoSession* m_pSessionMaster = nullptr;// 主UA客户端
    CInoSession* m_pSessionSlave = nullptr; // 备UA客户端
};

