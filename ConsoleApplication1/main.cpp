// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable : 4251)

#include <iostream>
#include <memory>
#include <assert.h>
#include "CInoUAClientProxyMgr.h"
#include <thread>
#include "format.h"

using namespace std;

int main()
{
    // fmt::print("Hello {}", "World!");
    // UA客户端适配器管理器
    shared_ptr<CInoUAClientProxyMgr> spClientProxyMgr = make_shared<CInoUAClientProxyMgr>();

    // UA客户端连接
    spClientProxyMgr->GetRtClientProxy();

    // UA客户端等待
    while (getchar() != 'q')
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
