// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

#include "CInoUAClient.h"
#include "CInoUAClientMgr.h"
#include "CInoUAClientProxy.h"

using namespace std;

int main()
{
    shared_ptr<CInoUAClient> spClient = make_shared<CInoUAClient>();

    shared_ptr<CInoUAClientMgr> spClientMgr = make_shared<CInoUAClientMgr>();

    shared_ptr<CInoUAClientProxy> spClientProxy = make_shared<CInoUAClientProxy>();

    std::cout << "Hello World!\n";
}
