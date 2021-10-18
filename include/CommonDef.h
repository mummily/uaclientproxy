#pragma once

// TODO∫Í
#define STR2(x)     #x 
#define STR(x)      STR2(x) 
#define TODO(desc)  message(__FILE__ "(" STR(__LINE__) "): " desc)

// …æ≥˝÷∏’Î∫Í
#define DelAndNil(pointer) \
    if (nullptr != pointer) { \
        delete pointer; \
        pointer = nullptr; \
    }

// …æ≥˝÷∏’Î¡–±Ì∫Í
#define DelAndNilList(ptrlist) \
    for (auto pointer : ptrlist) { \
        DelAndNil(pointer) \
    }