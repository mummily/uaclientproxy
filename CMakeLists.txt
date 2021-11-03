#[[ 说明：
    1. 应用程序ConsoleApplication1，库文件InoUAClientProxy
    2. ConsoleApplication1中调用InoUAClientProxy中的导出类
]]

cmake_minimum_required(VERSION 3.10)

# 设置工程名
set(PROJECT ConsoleApplication1)
project(${PROJECT})

# 头文件描述
set(HEADERS
)

# 源文件描述
set(SOURCES
    ./ConsoleApplication1/main.cpp
)

# 生成应用文件
add_executable(${PROJECT} 
    ${HEADERS}
    ${SOURCES}
)

# 添加头文件包含目录
include_directories(./include
    ./include/fmt
    ./include/ua
    ./include/ua/uabasecpp
    ./include/ua/uastack
    ./include/ua/uaclientcpp
    ./include/ua/uapkicpp
    ./InoUAClientProxy
)

#[[ TODO
    1. 区分Debug|Release
    2. 区分Win32|x64
]]

# 依赖库路径
target_link_directories(${PROJECT}
    PRIVATE ${PROJECT_SOURCE_DIR}/lib/ua/x86/debug
    PRIVATE ${PROJECT_SOURCE_DIR}/lib/fmt/x86/debug
)

# 依赖库描述
target_link_libraries(${PROJECT}
    uabasecppd.lib
    uastackd.lib
    uaclientcppd.lib
    uapkicppd.lib
    ws2_32.lib
    fmtd.lib
    InoUAClientProxy
)

# 添加子目录
add_subdirectory(InoUAClientProxy)