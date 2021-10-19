#pragma once

#include "InoUAClientProxyExport.h"

enum class emFAServerType;
class CInoUAClient;
class INO_EXPORT CInoUAClientMgr
{
public:
    CInoUAClientMgr(emFAServerType _emFAServerType);
    virtual ~CInoUAClientMgr();

public:
    // 获取主UA客户端
    CInoUAClient* getUAClient();

protected:

private:
    CInoUAClient* m_pUAClientMaster = nullptr;// 主UA客户端
    CInoUAClient* m_pUAClientSlave = nullptr; // 备UA客户端
};

