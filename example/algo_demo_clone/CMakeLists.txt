
find_package(OpenCV)

add_executable(AlgoDemo_clone)

target_sources(AlgoDemo_clone
    PRIVATE
    main.cpp    
)

target_link_libraries(AlgoDemo_clone
PUBLIC
    opencv_world
    demo_Algo
PRIVATE
    logging
)

target_include_directories(AlgoDemo_clone PUBLIC ./)

