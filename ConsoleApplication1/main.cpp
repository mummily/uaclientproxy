// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable : 4251)

#include <iostream>
#include <memory>
#include <assert.h>
#include "CInoUAClientProxyMgr.h"

using namespace std;

int main()
{
    // UA客户端适配器管理器
    shared_ptr<CInoUAClientProxyMgr> spClientProxyMgr = make_shared<CInoUAClientProxyMgr>();

    // UA客户端连接
    spClientProxyMgr->GetRtClientProxy();

    return 0;
}
