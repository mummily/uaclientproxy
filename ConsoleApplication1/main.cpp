// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable : 4251)

#include <iostream>
#include <memory>
#include <assert.h>
#include <thread>
#include "format.h"
#include <conio.h>

#include "CInoUAClientMgr.h"
#include "CInoUAClientConnect.h"
#include "CInoUAClientProxy.h"
#include "ScopeExit.h"
#include "InoCommonDef.h"

using namespace std;

int main()
{
    bool bOk = false;

    // UA客户端代理
    shared_ptr<CInoUAClientProxy> spClientProxy = make_shared<CInoUAClientProxy>();

    // UA客户端建立与某一服务器的连接
    CInoUAClientConnect* pClientConnect = spClientProxy->GetClientConnect(emFAServerType::RealTime);
    bOk = pClientConnect->connect();
    assert(bOk);

    // UA客户端断开与服务器的连接
    SCOPE_EXIT(
        bOk = pClientConnect->disconnect();
    assert(bOk);
    );

    CInoUAClientMgr* pUAClientMgr = pClientConnect->GetUAClientMgr();
    bOk = pUAClientMgr->read();
    assert(bOk);

    // UA客户端等待
    fmt::print("\n***************************************************\n");
    fmt::print(" Press {} to shutdown client\n", 'q');
    fmt::print("***************************************************\n");
    while (_getch() != 'q')
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
