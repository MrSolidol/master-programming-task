include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)
include(Catch)

cmake_minimum_required(VERSION 3.20)
add_library(introduction INTERFACE)
target_include_directories(introduction INTERFACE include)
file(GLOB TESTS tests/*.cpp)
add_executable(tests_introduction ${TESTS})
target_link_libraries(tests_introduction introduction Catch2::Catch2WithMain)
enable_testing()
catch_discover_tests(tests_introduction)