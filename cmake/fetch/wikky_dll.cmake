include(FetchContent)
if(NOT WIKKYDLL_Found)

# if(NOT DEFINED WIKKYDLL_URL)
# if(WIN32)
#      set(WIKKYDLL_URL "git@github.com:wikky250/wikky_dll.git")
# else()
#     message(FATEL_ERROR "Need Opencv4.5-linux package.")
# endif()
# endif()

# FetchContent_Declare(WIKKYDLL
#     URL ${OpenCV_URL}
# )
message(STATUS "Fetching WIKKYDLL : ${OpenCV_URL}")
FetchContent_MakeAvailable(WIKKYDLL)
message(STATUS "Fetching done")

FetchContent_GetProperties(WIKKYDLL SOURCE_DIR OpenCV_SOURCE_DIR)
message(STATUS "WIKKYDLL_DIR src dir : ${OpenCV_SOURCE_DIR}")
# get OpenCV_DIR
if(WIN32)
    set(WIKKYDLL_DIR ${OpenCV_SOURCE_DIR}/x64/vc15/lib)
endif()

endif()