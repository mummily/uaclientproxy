#include "CInoUAClientProxyMgr.h"

#include "uaplatformlayer.h"

CInoUAClientProxyMgr::CInoUAClientProxyMgr()
{

}

CInoUAClientProxyMgr::~CInoUAClientProxyMgr()
{

}

bool CInoUAClientProxyMgr::init()
{
    // Initialize the UA Stack platform layer
    UaPlatformLayer::init();

    return true;
}

bool CInoUAClientProxyMgr::cleanup()
{
    // Cleanup the UA Stack platform layer
    UaPlatformLayer::cleanup();
    return true;
}

bool CInoUAClientProxyMgr::connect()
{

    return true;
}
