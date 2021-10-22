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
#include "CInoUAClientProxy.h"
#include "CInoUAClientProxyMgr.h"
#include "ScopeExit.h"
#include "InoCommonDef.h"

using namespace std;

int main()
{
    bool bOk = false;

    // UA客户端适配器管理器
    shared_ptr<CInoUAClientProxyMgr> spClientProxyMgr = make_shared<CInoUAClientProxyMgr>();

    // UA客户端建立与服务器的连接
    CInoUAClientProxy* pClientProxy = spClientProxyMgr->GetClientProxy(emFAServerType::RealTime);
    bOk = pClientProxy->connect();
    assert(bOk);

    // UA客户端断开与服务器的连接
    SCOPE_EXIT(
        bOk = pClientProxy->disconnect();
    assert(bOk);
    );

    CInoUAClientMgr* pUAClientMgr = pClientProxy->GetUAClientMgr();
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
