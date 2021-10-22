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
    // ��ȡ�ͻ��˴���
    CInoUAClientConnect* GetClientConnect(emFAServerType serverType);

protected:

private:
    // ��ʼ��UA����
    bool init();
    // ���UA����
    void cleanup();

private:
    map<emFAServerType, CInoUAClientConnect*> m_mapClientConnect; // �ͻ��˴���
};

// using CInoUAClientConnectMgr = CInoUAClientProxy;