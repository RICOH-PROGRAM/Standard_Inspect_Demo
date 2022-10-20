include(FetchContent)

FetchContent_Declare(Qt5
    URL http://artifactory.smoa.cloud/artifactory/QT/qt-5.14.1_msvc2017.zip
)

FetchContent_MakeAvailable(Qt5)

FetchContent_GetProperties(Qt5 SOURCE_DIR Qt5_DIR)
list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})