
find_package(OpenCV)

add_executable(AlgoDemo)

target_sources(AlgoDemo
    PRIVATE
    main.cpp    
)

target_link_libraries(AlgoDemo
PUBLIC
    opencv_world
    demo_Algo
PRIVATE
    logging
)

target_include_directories(AlgoDemo PUBLIC ./)

