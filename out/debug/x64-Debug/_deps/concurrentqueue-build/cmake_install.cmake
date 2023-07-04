# Install script for directory: D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/MyCode/new_compose/Compass_Project/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue/concurrentqueueTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue/concurrentqueueTargets.cmake"
         "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-build/CMakeFiles/Export/a0893b6404edf66f9e8aae21e38f7549/concurrentqueueTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue/concurrentqueueTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue/concurrentqueueTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue" TYPE FILE FILES "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-build/CMakeFiles/Export/a0893b6404edf66f9e8aae21e38f7549/concurrentqueueTargets.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue" TYPE FILE FILES
    "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-build/concurrentqueueConfig.cmake"
    "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-build/concurrentqueueConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/concurrentqueue/moodycamel" TYPE FILE FILES
    "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-src/blockingconcurrentqueue.h"
    "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-src/concurrentqueue.h"
    "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-src/lightweightsemaphore.h"
    "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/concurrentqueue-src/LICENSE.md"
    )
endif()

