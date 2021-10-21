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

using namespace std;

int main()
{
    // fmt::print("Hello {}", "World!");
    // UA客户端适配器管理器
    shared_ptr<CInoUAClientProxyMgr> spClientProxyMgr = make_shared<CInoUAClientProxyMgr>();

    // UA客户端连接
    CInoUAClientProxy* pRtClientProxy = spClientProxyMgr->GetRtClientProxy();
    CInoUAClientMgr* pRtUAClientMgr = pRtClientProxy->GetUAClientMgr();
    bool bOk = pRtUAClientMgr->read();
    // assert(bOk);
    
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
