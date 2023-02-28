include(FetchContent)

FetchContent_Declare(
  yamlcpp
  GIT_REPOSITORY    https://github.com/jbeder/yaml-cpp.git
  GIT_TAG           master
)

FetchContent_MakeAvailable(yamlcpp)