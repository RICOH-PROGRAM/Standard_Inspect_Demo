
find_package(OpenCV)
find_package(Qt5 COMPONENTS Core Gui Widgets Network Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(AlgoDemo_QT)

target_sources(AlgoDemo_QT
    PRIVATE
    main.cpp
	algo_demo.h
	algo_demo.cpp
	algo_demo.ui
    imagewatch.h
    imagewatch.cpp
)

target_link_libraries(AlgoDemo_QT
PUBLIC
    opencv_world
PRIVATE
	Qt5::Widgets
	Qt5::Core	
    logging
    common
    base_alg
    algosettingdlg
)

target_include_directories(AlgoDemo_QT PUBLIC ./)

add_custom_command(
    TARGET AlgoDemo_QT
    POST_BUILD
    COMMAND "$<TARGET_FILE_DIR:Qt5::qmake>/windeployqt.exe" "--no-translations" $<TARGET_FILE:AlgoDemo_QT>
    WORKING_DIRECTORY $<TARGET_FILE_DIR:AlgoDemo_QT>
)

