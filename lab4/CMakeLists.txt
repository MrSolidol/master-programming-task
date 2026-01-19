cmake_minimum_required(VERSION 3.20)

include(FetchContent)

# --- Boost (headers only, correct way) ---
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.84.0
)
FetchContent_MakeAvailable(boost)

# Собираем все include-директории Boost
file(GLOB BOOST_INCLUDE_DIRS
     ${boost_SOURCE_DIR}/libs/*/include)

# --- Catch2 ---
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

include(CTest)
include(Catch)

add_library(iterator INTERFACE)
target_include_directories(iterator INTERFACE
    include
    ${BOOST_INCLUDE_DIRS}
)

file(GLOB TESTS tests/*.cpp)
add_executable(tests_iterator ${TESTS})
target_link_libraries(tests_iterator iterator Catch2::Catch2WithMain)

enable_testing()
catch_discover_tests(tests_iterator)
