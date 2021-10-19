#pragma once

// TODO宏
#define STR2(x)     #x 
#define STR(x)      STR2(x) 
#define TODO(desc)  message(__FILE__ "(" STR(__LINE__) "): " desc)

// 删除指针宏
#define DelAndNil(pointer)      \
    if (nullptr != pointer) {   \
        delete pointer;         \
        pointer = nullptr;      \
    }

// 删除指针列表宏
#define DelAndNilList(ptrlist)      \
    for (auto pointer : ptrlist) {  \
        DelAndNil(pointer)          \
    }

#ifdef INO_PRINTF
#define printf(fmt,...) printf(__FUNCTION__ "(" STR(__LINE__) "): " fmt, __VA_ARGS__)
#endif

// 服务类型
enum class emFAServerType
{
    RealTime = 0, // 实时服务
    IO // IO服务
};