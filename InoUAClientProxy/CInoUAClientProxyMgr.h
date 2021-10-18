#pragma once
#include "export.h"
#include <map>
#include <string>

using namespace std;

class SampleClient;
class INO_EXPORT CInoUAClientProxyMgr
{
public:
    CInoUAClientProxyMgr();
    virtual ~CInoUAClientProxyMgr();

public:
    // 连接客户端
    bool connect(const string& sURL);

protected:

private:
    // 初始化UA环境
    bool init();
    // 清除UA环境
    bool cleanup();

private:
    map<string, SampleClient*> m_mapClient;
};
