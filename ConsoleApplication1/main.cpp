// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable : 4251)

#include <iostream>
#include <memory>
#include <assert.h>
#include <thread>
#include "format.h"
#include <conio.h>

#include "InoSession.h"
#include "InoRedSession.h"
#include "InoSessionGroup.h"
#include "ScopeExit.h"
#include "InoCommonDef.h"

using namespace std;

class Test
{};

int reallyMain()
{
    UaPointerArray<Test> ta;

    UaStatus status = !OpcUa_Good;

    // UA客户端代理
    shared_ptr<InoSessionGroup> spSessionGroup = make_shared<InoSessionGroup>();

    // UA客户端建立与某一服务器的连接
    InoRedSession* pRedClient = spSessionGroup->getRedSession(emFAServerType::RealTime);
    // status = pRedClient->connect();

    // UA客户端断开与服务器的连接
    SCOPE_EXIT(
        status = pRedClient->disconnect();
    assert(status.isGood());
    );

    InoSession* pSession = pRedClient->getSession();
    // pSession->read();
    assert(status.isGood());

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

int main()
{
    return reallyMain();
}