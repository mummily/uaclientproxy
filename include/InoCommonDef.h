#pragma once

// TODO��
#define STR2(x)     #x 
#define STR(x)      STR2(x) 
#define TODO(desc)  message(__FILE__ "(" STR(__LINE__) "): " desc)

// ɾ��ָ���
#define DelAndNil(pointer)      \
    if (nullptr != pointer) {   \
        delete pointer;         \
        pointer = nullptr;      \
    }

// ɾ��ָ���б��
#define DelAndNilList(ptrlist)      \
    for (auto pointer : ptrlist) {  \
        DelAndNil(pointer)          \
    }

#ifdef INO_PRINTF
#define printf(fmt,...) printf(__FUNCTION__ "(" STR(__LINE__) "): " fmt, __VA_ARGS__)
#endif

// ��������
enum class emFAServerType
{
    RealTime = 0, // ʵʱ����
    IO // IO����
};