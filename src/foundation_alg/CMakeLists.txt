
find_package(Qt5 COMPONENTS Core REQUIRED)
add_library(demo_Algo SHARED "")

target_sources(demo_Algo
PUBLIC 
    foundation.h
    implfoundation.h
PRIVATE 
    foundation.cpp
    implfoundation.cpp
)
target_include_directories(demo_Algo
PUBLIC
if(NOT DEFINE WIKKYDLL_DIR)
    ${THIRDPARTY_DIR}/wikkydll/include
else()
    ${WIKKYDLL_DIR}/src/AlgDll
endif()
)

if(NOT DEFINED WIKKYDLL_DIR)
target_link_libraries(demo_Algo
PUBLIC 
    algosettingdlg
    logging
    common
    base_alg
    Qt5::Core
    yaml-cpp
PRIVATE
    algosettingdlg
    ${THIRDPARTY_DIR}/wikkydll/lib/wikky_dll.lib
)
endif()
if(DEFINED WIKKYDLL_DIR) 
target_link_libraries(demo_Algo
PUBLIC 
    algosettingdlg
    logging
    common
    base_alg
    Qt5::Core
    yaml-cpp
PRIVATE
    algosettingdlg
    ${THIRDPARTY_DIR}/wikkydll/lib/wikky_dll.lib
)
endif()
