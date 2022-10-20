include(FetchContent)
if(NOT Opencv_Found)

if(NOT DEFINED OpenCV_URL)
if(WIN32)
    set(OpenCV_URL "https://devops-generic.pkg.coding.smoa.cloud/suanfabianjigongju/3rdparty/opencv-4.5.5-vc14_vc15.zip")
else()
    message(FATEL_ERROR "Need Opencv4.5-linux package.")
endif()
endif()

FetchContent_Declare(OpenCV
    URL ${OpenCV_URL}
)
message(STATUS "Fetching opencv : ${OpenCV_URL}")
FetchContent_MakeAvailable(OpenCV)
message(STATUS "Fetching done")

FetchContent_GetProperties(OpenCV SOURCE_DIR OpenCV_SOURCE_DIR)
message(STATUS "OpenCV src dir : ${OpenCV_SOURCE_DIR}")
# get OpenCV_DIR
if(WIN32)
    set(OpenCV_DIR ${OpenCV_SOURCE_DIR}/x64/vc15/lib)
else()
    set(OpenCV_DIR ${OpenCV_SOURCE_DIR}/lib/cmake/opencv4)
endif()

endif()