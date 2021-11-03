#pragma once

#include "InoExportDef.h"
#include <map>
#include <string>
#include <tuple>

using namespace std;

class InoRedSession;
enum class emFAServerType;
class UaUniString;
class InoSessionConfig;
class INO_EXPORT InoSessionGroup
{
public:
    InoSessionGroup();
    virtual ~InoSessionGroup();

public:
    // 获取客户端代理
    InoRedSession* getRedSession(emFAServerType serverType);

protected:

private:
    // 初始化UA环境
    bool init();
    // 清除UA环境
    void cleanup();
    // 获取客户端配置
    UaUniString getConfigPath();

private:
    map<emFAServerType, InoRedSession*> m_mapRedSession; // 客户端代理
    map<emFAServerType, InoSessionConfig*> m_mapRedSessionConfig; // 客户端配置
    InoSessionConfig* m_pSessionConfig = nullptr;
};