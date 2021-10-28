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
    // ��ȡ�ͻ��˴���
    CInoRedSession* getRedSession(emFAServerType serverType);

protected:

private:
    // ��ʼ��UA����
    bool init();
    // ���UA����
    void cleanup();
    // ��ȡ�ͻ�������
    UaUniString getConfigPath();

private:
    map<emFAServerType, CInoRedSession*> m_mapRedSession; // �ͻ��˴���
    map<emFAServerType, CInoSessionConfig*> m_mapRedSessionConfig; // �ͻ�������
    CInoSessionConfig* m_pSessionConfig = nullptr;
};