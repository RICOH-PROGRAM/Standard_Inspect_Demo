

add_library(base_alg INTERFACE)

target_sources(base_alg INTERFACE ibasealgorithm.h)

target_include_directories(base_alg INTERFACE 
./
)

target_link_libraries(base_alg
INTERFACE
	common
	logging
)