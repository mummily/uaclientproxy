#pragma once

// TODO��
#define STR2(x)     #x 
#define STR(x)      STR2(x) 
#define TODO(desc)  message(__FILE__ "(" STR(__LINE__) "): " desc)

// ɾ��ָ���
#define DelAndNil(pointer) \
    if (nullptr != pointer) { \
        delete pointer; \
        pointer = nullptr; \
    }

// ɾ��ָ���б��
#define DelAndNilList(ptrlist) \
    for (auto pointer : ptrlist) { \
        DelAndNil(pointer) \
    }