#[[ 说明：
    1. 应用程序ConsoleApplication1，库文件InoUAClientProxy
    2. ConsoleApplication1中调用InoUAClientProxy中的导出类
]]

cmake_minimum_required(VERSION 3.10)

# 设置工程名
project(ConsoleApplication1)

# 头文件描述
set(HEADERS
)

# 源文件描述
set(SOURCES
    ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/main.cpp
)

# 生成应用文件
add_executable(${PROJECT_NAME} 
    ${HEADERS}
    ${SOURCES}
)

# 添加头文件包含目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/fmt
    ${PROJECT_SOURCE_DIR}/include/ua
    ${PROJECT_SOURCE_DIR}/include/ua/uabasecpp
    ${PROJECT_SOURCE_DIR}/include/ua/uastack
    ${PROJECT_SOURCE_DIR}/include/ua/uaclientcpp
    ${PROJECT_SOURCE_DIR}/include/ua/uapkicpp
    ${PROJECT_SOURCE_DIR}/InoUAClientProxy
)

#[[ TODO 依赖库路径
    1. 区分Debug|Release
    2. 区分Win32|x64
]]

# 依赖库路径
target_link_directories(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/lib/ua/x86/debug
    PRIVATE ${PROJECT_SOURCE_DIR}/lib/fmt/x86/debug
)

# 依赖库描述
target_link_libraries(${PROJECT_NAME} 
    PRIVATE debug uabasecppd.lib optimized uabasecpp.lib
    PRIVATE debug uastackd.lib optimized uastack.lib
    PRIVATE debug uaclientcppd.lib optimized uaclientcpp.lib
    PRIVATE debug uapkicppd.lib optimized uapkicpp.lib
    PRIVATE debug fmtd.lib optimized fmt.lib
    PRIVATE ws2_32.lib
    PRIVATE InoUAClientProxy
)

# 添加子目录
add_subdirectory(InoUAClientProxy)