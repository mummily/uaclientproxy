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
    // ��ȡ�ͻ��˴���
    CInoUAClientProxy* GetClientProxy(emFAServerType serverType);
    // ��ȡʵʱ����ͻ��˴���
    CInoUAClientProxy* GetRtClientProxy();

protected:

private:
    // ��ʼ��UA����
    bool init();
    // ���UA����
    void cleanup();

private:
    CInoUAClientProxy* m_pRtClientProxy = nullptr; // ʵʱ����ͻ��˴���
    CInoUAClientProxy* m_pIOClientProxy = nullptr; // IO����ͻ��˴���
};
