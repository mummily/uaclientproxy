#pragma once

#include "InoExportDef.h"

class UaStatus;
class UaString;
class UaNodeIdArray;
class InoSession;
class InoSessionConfig;
class INO_EXPORT InoRedSession
{
public:
    InoRedSession();
    virtual ~InoRedSession();

public:
    // 连接服务器
    UaStatus connect(const UaString& serverUrl1, const UaString& serverUrl2);
    // 断开与客户端的连接
    UaStatus disconnect();
    // 获取主UA客户端
    InoSession* getSession();
    // 设置配置信息
    void setConfiguration(InoSessionConfig* pConfigMaster, InoSessionConfig* pConfigSlave);
    // 读取
    bool read(const UaNodeIdArray& nodes);

protected:

private:
    InoSession* m_pSessionMaster = nullptr;// 主UA客户端
    InoSession* m_pSessionSlave = nullptr; // 备UA客户端
};

