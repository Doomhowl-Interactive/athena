cmake_minimum_required(VERSION 3.15)
project(minerva-tests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    tests.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

add_test(AllTestsInMain ${PROJECT_NAME})