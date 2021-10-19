#include "CInoUAClientMgr.h"
#include "CInoUAClient.h"
#include "InoCommonDef.h"

CInoUAClientMgr::CInoUAClientMgr(emFAServerType _emFAServerType)
{
    m_pUAClientMaster = new CInoUAClient(_emFAServerType);
    m_pUAClientSlave = new CInoUAClient(_emFAServerType);
}

CInoUAClientMgr::~CInoUAClientMgr()
{
    DelAndNil(m_pUAClientMaster);
    DelAndNil(m_pUAClientSlave);
}

CInoUAClient* CInoUAClientMgr::getUAClient()
{
    return m_pUAClientMaster;
}
