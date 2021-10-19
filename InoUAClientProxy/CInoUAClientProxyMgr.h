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
    // ��ʼ��UA����
    bool init();
    // ���UA����
    void cleanup();

private:
    CInoUAClientProxy* m_pRtClientProxy = nullptr; // ʵʱ����ͻ��˴���
    CInoUAClientProxy* m_pIOClientProxy = nullptr; // IO����ͻ��˴���
};
