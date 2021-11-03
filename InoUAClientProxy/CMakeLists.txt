#[[ 说明：
    1. 共享库文件 InoUAClientProxy
    2. 导出部分类供其它程序调用
]]

# 设置工程名
set(PROJECT InoUAClientProxy)

# 头文件描述
file(GLOB_RECURSE HEADER *.h)

# 源文件描述
file(GLOB_RECURSE SOURCE *.cpp)

# 编译预定义描述
add_compile_definitions(
    INOUACLIENTPROXY_EXPORTS
)

# 添加头文件包含目录
include_directories(${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/fmt
    ${PROJECT_SOURCE_DIR}/include/ua
    ${PROJECT_SOURCE_DIR}/include/ua/uabasecpp
    ${PROJECT_SOURCE_DIR}/include/ua/uastack
    ${PROJECT_SOURCE_DIR}/include/ua/uaclientcpp
    ${PROJECT_SOURCE_DIR}/include/ua/uapkicpp
)

# 三方库描述：uabasecpp
add_library(uabasecpp SHARED IMPORTED)
set_target_properties(uabasecpp PROPERTIES 
    IMPORTED_IMPLIB_DEBUG "${PROJECT_SOURCE_DIR}/lib/ua/x86/debug/uabasecppd.lib"
    IMPORTED_IMPLIB_RELEASE ""
    IMPORTED_LOCATION_DEBUG "${PROJECT_SOURCE_DIR}/Debug/uabasecppd.dll"
    IMPORTED_LOCATION_RELEASE ""
)
# 三方库描述：uastack
add_library(uastack SHARED IMPORTED)
set_target_properties(uastack PROPERTIES 
    IMPORTED_IMPLIB_DEBUG "${PROJECT_SOURCE_DIR}/lib/ua/x86/debug/uastackd.lib"
    IMPORTED_IMPLIB_RELEASE ""
    IMPORTED_LOCATION_DEBUG "${PROJECT_SOURCE_DIR}/Debug/uastackd.dll"
    IMPORTED_LOCATION_RELEASE ""
)
# 三方库描述：uaclientcpp
add_library(uaclientcpp SHARED IMPORTED)
set_target_properties(uaclientcpp PROPERTIES 
    IMPORTED_IMPLIB_DEBUG "${PROJECT_SOURCE_DIR}/lib/ua/x86/debug/uaclientcppd.lib"
    IMPORTED_IMPLIB_RELEASE ""
    IMPORTED_LOCATION_DEBUG "${PROJECT_SOURCE_DIR}/Debug/uaclientcppd.dll"
    IMPORTED_LOCATION_RELEASE ""
)
# 三方库描述：uapkicpp
add_library(uapkicpp SHARED IMPORTED)
set_target_properties(uapkicpp PROPERTIES 
    IMPORTED_IMPLIB_DEBUG "${PROJECT_SOURCE_DIR}/lib/ua/x86/debug/uapkicppd.lib"
    IMPORTED_IMPLIB_RELEASE ""
    IMPORTED_LOCATION_DEBUG "${PROJECT_SOURCE_DIR}/Debug/uapkicppd.dll"
    IMPORTED_LOCATION_RELEASE ""
)
# 三方库描述：fmt
add_library(fmt SHARED IMPORTED)
set_target_properties(fmt PROPERTIES 
    IMPORTED_IMPLIB_DEBUG "${PROJECT_SOURCE_DIR}/lib/fmt/x86/debug/fmtd.lib"
    IMPORTED_IMPLIB_RELEASE ""
    IMPORTED_LOCATION_DEBUG "${PROJECT_SOURCE_DIR}/Debug/fmtd.dll"
    IMPORTED_LOCATION_RELEASE ""
)

# 生成共享库文件
add_library(${PROJECT} SHARED 
    ${SOURCE} 
    ${HEADER}
)

# 依赖库描述
target_link_libraries(${PROJECT}
    uabasecpp
    uastack
    uaclientcpp
    uapkicpp
    ws2_32.lib
    fmt
)

# source_group("src" FILES ${lib_SOURCES})
# source_group("headers" FILES ${lib_HEADERS})