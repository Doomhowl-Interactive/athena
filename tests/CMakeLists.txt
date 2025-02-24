cmake_minimum_required(VERSION 3.15)
project(minerva-tests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gtest via vcpkg is broken
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(${PROJECT_NAME}
    tests.cc
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    minerva
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})