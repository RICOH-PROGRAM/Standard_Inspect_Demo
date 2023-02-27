
find_package(Qt5 COMPONENTS Core REQUIRED)
add_library(demo_Algo SHARED "")

target_sources(demo_Algo
PUBLIC 
    foundation.h
PRIVATE 
    foundation.cpp
    implfoundation.h
    implfoundation.cpp
)
target_link_libraries(demo_Algo
PRIVATE
    logging
    common
    base_alg
    Qt5::Core
    algosettingdlg
)
