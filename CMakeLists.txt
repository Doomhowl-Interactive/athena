cmake_minimum_required(VERSION 3.15)
project(minerva)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(MINERVA_BUILD_EXAMPLE "Build the example" OFF)
option(MINERVA_BUILD_TESTS "Build the tests" OFF)

if (WIN32)
    # I don't understand dynamic linking on Windows yet
    # and I don't really care for now... ¯\_(ツ)_/¯ 
    set(BUILD_TYPE STATIC)
else()
    set(BUILD_TYPE SHARED)
endif()

# TODO: Add lib for reader, writer.
find_package(lz4 REQUIRED)

add_library(${PROJECT_NAME} ${BUILD_TYPE}
    include/minerva/buffer.hh
    include/minerva/compressed_buffer.hh
    include/minerva/core.hh
    include/minerva/exceptions.hh
    include/minerva/file_stream_reader.hh
    include/minerva/file_stream_writer.hh
    include/minerva/stream_reader.hh
    include/minerva/stream_writer.hh

    src/buffer.cc
    src/compressed_buffer.cc
    src/file_stream_reader.cc
    src/file_stream_writer.cc
)

target_link_libraries(${PROJECT_NAME} PUBLIC lz4::lz4)
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(MINERVA_BUILD_EXAMPLE)
    add_subdirectory(sandbox)
endif()

if (MINERVA_BUILD_TESTS)
    add_subdirectory(tests)
endif()