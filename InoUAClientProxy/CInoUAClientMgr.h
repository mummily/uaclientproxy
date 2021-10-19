#pragma once

#include "InoExportDef.h"

class UaStatus;
class CInoUAClient;
class CInoUAClientConfig;
class INO_EXPORT CInoUAClientMgr
{
public:
    CInoUAClientMgr();
    virtual ~CInoUAClientMgr();

public:
    // 连接服务器
    UaStatus connect();
    // 获取主UA客户端
    CInoUAClient* getUAClient();
    // 设置配置信息
    void setConfiguration(CInoUAClientConfig* pConfiguration);
    // 获取配置信息
    CInoUAClientConfig* getConfiguration();

protected:

private:
    CInoUAClient* m_pUAClientMaster = nullptr;// 主UA客户端
    CInoUAClient* m_pUAClientSlave = nullptr; // 备UA客户端
};

