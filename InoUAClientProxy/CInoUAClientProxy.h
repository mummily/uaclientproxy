#pragma once

#include "InoExportDef.h"
#include <map>
#include <string>
#include <tuple>

using namespace std;

class CInoUARedClient;
enum class emFAServerType;
class UaUniString;
class CInoUAClientConfig;
class INO_EXPORT CInoUAClientProxy
{
public:
    CInoUAClientProxy();
    virtual ~CInoUAClientProxy();

public:
    // 获取客户端代理
    CInoUARedClient* getRedClient(emFAServerType serverType);

protected:

private:
    // 初始化UA环境
    bool init();
    // 清除UA环境
    void cleanup();
    // 获取客户端配置
    UaUniString getConfigPath();

private:
    map<emFAServerType, CInoUARedClient*> m_mapClientConnect; // 客户端代理
    map<emFAServerType, CInoUAClientConfig*> m_mapClientConfig; // 客户端配置
    CInoUAClientConfig* m_pUAClientConfig = nullptr;
};

// using CInoUAClientConnectMgr = CInoUAClientProxy;