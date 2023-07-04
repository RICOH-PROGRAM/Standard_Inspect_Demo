# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-src"
  "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-build"
  "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix"
  "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/tmp"
  "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp"
  "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src"
  "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
