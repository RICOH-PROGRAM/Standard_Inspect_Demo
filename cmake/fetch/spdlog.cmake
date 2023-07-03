include(FetchContent)

FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.11.0
)

FetchContent_MakeAvailable(spdlog)
#
#set(spdlog_BUILD_TESTS OFF) # 设置好变量用于关掉AAA项目的测试
#
#FetchContent_GetProperties(spdlog)
#if(NOT spdlog_POPULATED) 
#  FetchContent_Populate(spdlog)
#  add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
#endif ()
