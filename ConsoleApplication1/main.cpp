// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable : 4251)

#include <iostream>
#include <memory>
#include <assert.h>

#include "ScopeExit.h"
#include "CInoUAClient.h"
#include "CInoUAClientMgr.h"
#include "CInoUAClientProxy.h"
#include "CInoUAClientProxyMgr.h"
#include "CommonDef.h"

using namespace std;

int main()
{
#pragma region 验证调用
    // shared_ptr<CInoUAClient> spClient = make_shared<CInoUAClient>();
    // shared_ptr<CInoUAClientMgr> spClientMgr = make_shared<CInoUAClientMgr>();
    // shared_ptr<CInoUAClientProxy> spClientProxy = make_shared<CInoUAClientProxy>();
#pragma endregion

    // UA客户端适配器管理器 初始化&清理
    shared_ptr<CInoUAClientProxyMgr> spClientProxyMgr = make_shared<CInoUAClientProxyMgr>();

    // UA客户端连接
    string sURL("opc.tcp://localhost:48010");
    spClientProxyMgr->connect(sURL);

    std::cout << "Hello World!\n";
}
