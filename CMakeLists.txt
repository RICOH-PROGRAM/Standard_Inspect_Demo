cmake_minimum_required(VERSION 3.15)
project(Compass_Project VERSION 0.1.0 LANGUAGES CXX)
find_package(Qt5 COMPONENTS Core Gui Widgets Network Sql REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(fetch/spdlog)
include(fetch/json)
include(fetch/OpenCV)
include(fetch/concurrentqueue)
include(fetch/third_party)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# 打开以下set指令，可以指定本地三方依赖库地址，跳过从网络下载
#set (THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)
if(NOT DEFINED THIRDPARTY_DIR)
    include(fetch/third_party)
endif()

set(OpenCV_DIR ${THIRDPARTY_DIR}/opencv/x64/vc15/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_compile_options(
    $<$<AND:$<NOT:$<COMPILE_LANGUAGE:CUDA>>,$<OR:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>>:/utf-8>
)

add_subdirectory(src)
if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
    add_subdirectory(example-demo)
endif()