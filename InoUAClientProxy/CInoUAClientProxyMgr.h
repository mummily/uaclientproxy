#pragma once

#include "InoExportDef.h"
#include <map>
#include <string>

using namespace std;

class CInoUAClientConnect;
enum class emFAServerType;
class INO_EXPORT CInoUAClientProxyMgr
{
public:
    CInoUAClientProxyMgr();
    virtual ~CInoUAClientProxyMgr();

public:
    // ��ȡ�ͻ��˴���
    CInoUAClientConnect* GetClientProxy(emFAServerType serverType);

protected:

private:
    // ��ʼ��UA����
    bool init();
    // ���UA����
    void cleanup();

private:
    map<emFAServerType, CInoUAClientConnect*> m_mapClientProxy; // �ͻ��˴���
};
