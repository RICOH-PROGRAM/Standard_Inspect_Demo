find_package(OpenCV)
find_package(Qt5 COMPONENTS Core Gui Widgets Network Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(algosettingdlg STATIC)

target_sources(algosettingdlg
PUBLIC
	algosettingdlg.h
	algosettingdlg.cpp
	algosettingdlg.ui
)

target_link_libraries(algosettingdlg
PUBLIC
	Qt5::Widgets
	Qt5::Core
    logging
	common
)

target_include_directories(algosettingdlg 
PUBLIC
	./
)
