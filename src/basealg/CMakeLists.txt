

add_library(base_camera INTERFACE)

target_sources(base_camera INTERFACE icameradevice.h)

target_include_directories(base_camera INTERFACE ./)