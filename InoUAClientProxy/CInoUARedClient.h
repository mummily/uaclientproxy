#pragma once

#include "InoExportDef.h"

// class UaStatus;
class CInoUAClient;
class CInoUAClientConfig;
class INO_EXPORT CInoUARedClient
{
public:
    CInoUARedClient();
    virtual ~CInoUARedClient();

public:
    // 连接服务器
    /*UaStatus*/bool connect();
    // 断开与客户端的连接
    /*UaStatus*/bool disconnect();
    // 是否连接服务器
    bool isconnect();
    // 获取主UA客户端
    CInoUAClient* getUAClient();
    // 设置配置信息
    void setConfiguration(CInoUAClientConfig* pConfigMaster, CInoUAClientConfig* pConfigSlave);
    // 读取
    bool read();

protected:

private:
    CInoUAClient* m_pUAClientMaster = nullptr;// 主UA客户端
    CInoUAClient* m_pUAClientSlave = nullptr; // 备UA客户端
};

