
add_library(demo_Algo SHARED "")

target_sources(demo_Algo
PUBLIC 
    foundation.h
    implfoundation.h
PRIVATE 
    foundation.cpp
    implfoundation.cpp
)

target_link_libraries(demo_Algo
PUBLIC 
    logging
    common
    base_alg
)