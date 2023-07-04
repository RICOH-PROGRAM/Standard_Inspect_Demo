# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/yamlcpp-populate-gitclone-lastrun.txt" AND EXISTS "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/yamlcpp-populate-gitinfo.txt" AND
  "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/yamlcpp-populate-gitclone-lastrun.txt" IS_NEWER_THAN "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/yamlcpp-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/yamlcpp-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/bin/git.exe" 
            clone --no-checkout --config "advice.detachedHead=false" "D:/MyCode/third_party/yaml-cpp" "yamlcpp-src"
    WORKING_DIRECTORY "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'D:/MyCode/third_party/yaml-cpp'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/bin/git.exe" 
          checkout "master" --
  WORKING_DIRECTORY "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/bin/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/yamlcpp-populate-gitinfo.txt" "D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/yamlcpp-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'D:/MyCode/new_compose/Compass_Project/out/debug/x64-Debug/_deps/yamlcpp-subbuild/yamlcpp-populate-prefix/src/yamlcpp-populate-stamp/yamlcpp-populate-gitclone-lastrun.txt'")
endif()
