#pragma once
#include "export.h"

class INO_EXPORT CInoUAClientProxyMgr
{
public:
    CInoUAClientProxyMgr();
    virtual ~CInoUAClientProxyMgr();

public:
    // 初始化UA环境
    bool init();
    // 清除UA环境
    bool cleanup();
    // 连接客户端
    bool connect();

protected:

private:

};
