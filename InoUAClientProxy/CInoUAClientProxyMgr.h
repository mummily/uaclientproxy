#pragma once
#include "export.h"

class INO_EXPORT CInoUAClientProxyMgr
{
public:
    CInoUAClientProxyMgr();
    virtual ~CInoUAClientProxyMgr();

public:
    // ��ʼ��UA����
    bool init();
    // ���UA����
    bool cleanup();
    // ���ӿͻ���
    bool connect();

protected:

private:

};
