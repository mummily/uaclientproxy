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
    // ��ȡ�ͻ��˴���
    CInoUARedClient* getRedClient(emFAServerType serverType);

protected:

private:
    // ��ʼ��UA����
    bool init();
    // ���UA����
    void cleanup();
    // ��ȡ�ͻ�������
    UaUniString getConfigPath();

private:
    map<emFAServerType, CInoUARedClient*> m_mapClientConnect; // �ͻ��˴���
    map<emFAServerType, CInoUAClientConfig*> m_mapClientConfig; // �ͻ�������
    CInoUAClientConfig* m_pUAClientConfig = nullptr;
};

// using CInoUAClientConnectMgr = CInoUAClientProxy;