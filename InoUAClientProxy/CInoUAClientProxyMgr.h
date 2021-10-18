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
    // ���ӿͻ���
    bool connect(const string& sURL);

protected:

private:
    // ��ʼ��UA����
    bool init();
    // ���UA����
    bool cleanup();

private:
    map<string, SampleClient*> m_mapClient;
};
