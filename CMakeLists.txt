cmake_minimum_required(VERSION 3.10)

project(ConsoleApplication1)

include_directories(./include
    ./include/fmt
    ./include/ua
    ./include/ua/uabasecpp
    ./include/ua/uastack
    ./include/ua/uaclientcpp
    ./include/ua/uapkicpp
    ./InoUAClientProxy
)

add_executable(ConsoleApplication1 ./ConsoleApplication1/main.cpp)

target_link_libraries(ConsoleApplication1
    ${PROJECT_SOURCE_DIR}/lib/ua/x86/debug/uabasecppd.lib
    ${PROJECT_SOURCE_DIR}/lib/ua/x86/debug/uastackd.lib
    ${PROJECT_SOURCE_DIR}/lib/ua/x86/debug/uaclientcppd.lib
    ${PROJECT_SOURCE_DIR}/lib/ua/x86/debug/uapkicppd.lib
    ws2_32.lib
    ${PROJECT_SOURCE_DIR}/lib/fmt/x86/debug/fmtd.lib
    InoUAClientProxy
)

add_subdirectory(InoUAClientProxy)