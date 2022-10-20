

add_library(Alg_foundation SHARED "")

target_sources(Alg_foundation
PUBLIC 
    foundation.h
PRIVATE 
    foundation.cpp
)
target_link_libraries(Alg_foundation
PUBLIC
    base_alg
PRIVATE
    logging
)
