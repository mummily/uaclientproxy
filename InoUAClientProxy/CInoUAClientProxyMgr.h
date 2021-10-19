#pragma once

#include "InoUAClientProxyExport.h"
#include <map>
#include <string>

using namespace std;

class CInoUAClientProxy;
class INO_EXPORT CInoUAClientProxyMgr
{
public:
    CInoUAClientProxyMgr();
    virtual ~CInoUAClientProxyMgr();

public:
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
