#pragma once

#include "InoExportDef.h"
#include <map>
#include <string>

using namespace std;

class CInoUAClientProxy;
enum class emFAServerType;
class INO_EXPORT CInoUAClientProxyMgr
{
public:
    CInoUAClientProxyMgr();
    virtual ~CInoUAClientProxyMgr();

public:
    // 获取客户端代理
    CInoUAClientProxy* GetClientProxy(emFAServerType serverType);

protected:

private:
    // 初始化UA环境
    bool init();
    // 清除UA环境
    void cleanup();

private:
    map<emFAServerType, CInoUAClientProxy*> m_mapClientProxy; // 客户端代理
};
