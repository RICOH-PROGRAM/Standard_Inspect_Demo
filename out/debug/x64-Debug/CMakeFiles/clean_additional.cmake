# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "example-demo\\algo_demo\\AlgoDemo_autogen"
  "example-demo\\algo_demo\\CMakeFiles\\AlgoDemo_autogen.dir\\AutogenUsed.txt"
  "example-demo\\algo_demo\\CMakeFiles\\AlgoDemo_autogen.dir\\ParseCache.txt"
  "src\\algosettingdlg\\CMakeFiles\\algosettingdlg_autogen.dir\\AutogenUsed.txt"
  "src\\algosettingdlg\\CMakeFiles\\algosettingdlg_autogen.dir\\ParseCache.txt"
  "src\\algosettingdlg\\algosettingdlg_autogen"
  "src\\foundation_alg\\CMakeFiles\\demo_Algo_autogen.dir\\AutogenUsed.txt"
  "src\\foundation_alg\\CMakeFiles\\demo_Algo_autogen.dir\\ParseCache.txt"
  "src\\foundation_alg\\demo_Algo_autogen"
  )
endif()
