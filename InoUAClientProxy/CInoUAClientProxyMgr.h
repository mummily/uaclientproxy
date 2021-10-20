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
    // 获取实时服务客户端代理
    CInoUAClientProxy* GetRtClientProxy();

protected:

private:
    // 初始化UA环境
    bool init();
    // 清除UA环境
    void cleanup();

private:
    CInoUAClientProxy* m_pRtClientProxy = nullptr; // 实时服务客户端代理
    CInoUAClientProxy* m_pIOClientProxy = nullptr; // IO服务客户端代理
};
