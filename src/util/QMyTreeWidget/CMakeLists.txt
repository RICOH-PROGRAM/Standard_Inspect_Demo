
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
add_library(qmytreewidget SHARED "")

target_sources(qmytreewidget
PUBLIC 
qmytreewidget.h
PRIVATE 
    qmytreewidget.cpp
)
target_link_libraries(qmytreewidget
PRIVATE
    logging
    common
    Qt5::Widgets
    yaml-cpp
)
