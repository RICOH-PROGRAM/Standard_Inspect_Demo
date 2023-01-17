

add_library(demo_Algo SHARED "")

target_sources(demo_Algo
PUBLIC 
    foundation.h
PRIVATE 
    foundation.cpp
)
target_link_libraries(demo_Algo
PRIVATE
    logging
    common
    base_alg
)
