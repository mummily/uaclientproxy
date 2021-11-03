#pragma once

#include "InoExportDef.h"
#include <map>
#include <string>
#include <tuple>

using namespace std;

class CInoRedSession;
enum class emFAServerType;
class UaUniString;
class CInoSessionConfig;
class INO_EXPORT CInoSessionGroup
{
public:
    CInoSessionGroup();
    virtual ~CInoSessionGroup();

public:
    // 获取客户端代理
    CInoRedSession* getRedSession(emFAServerType serverType);

protected:

private:
    // 初始化UA环境
    bool init();
    // 清除UA环境
    void cleanup();
    // 获取客户端配置
    UaUniString getConfigPath();

private:
    map<emFAServerType, CInoRedSession*> m_mapRedSession; // 客户端代理
    map<emFAServerType, CInoSessionConfig*> m_mapRedSessionConfig; // 客户端配置
    CInoSessionConfig* m_pSessionConfig = nullptr;
};