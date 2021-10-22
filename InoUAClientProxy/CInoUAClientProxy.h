#pragma once

#include "InoExportDef.h"
#include <map>
#include <string>

using namespace std;

class CInoUAClientConnect;
enum class emFAServerType;
class INO_EXPORT CInoUAClientProxy
{
public:
    CInoUAClientProxy();
    virtual ~CInoUAClientProxy();

public:
    // 获取客户端代理
    CInoUAClientConnect* GetClientConnect(emFAServerType serverType);

protected:

private:
    // 初始化UA环境
    bool init();
    // 清除UA环境
    void cleanup();

private:
    map<emFAServerType, CInoUAClientConnect*> m_mapClientConnect; // 客户端代理
};

// using CInoUAClientConnectMgr = CInoUAClientProxy;