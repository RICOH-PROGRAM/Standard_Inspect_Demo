find_package(OpenCV)
find_package(Qt5 COMPONENTS Core Gui Widgets Network Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(algosettingdlg INTERFACE)

target_sources(algosettingdlg
INTERFACE
	algosettingdlg.h
	MyGraphicsView.h
	algosettingdlg.cpp
	algosettingdlg.ui
	MyGraphicsView.cpp
)

target_link_libraries(algosettingdlg
INTERFACE
	Qt5::Widgets
	Qt5::Core
    logging
	common
	qmytreewidget
	yaml-cpp
)

target_include_directories(algosettingdlg 
INTERFACE
	./
)
