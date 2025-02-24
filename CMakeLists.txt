cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Athena)

option(ATHENA_BUILD_EXAMPLE "Build the example" OFF)

find_package(lz4 REQUIRED)

# TODO: Add lib for reader, writer. Use upstream lz4 if possible.

if (WIN32)
    # I don't understand dynamic linking on Windows yet
    # and I don't really care for now... ¯\_(ツ)_/¯ 
    set(BUILD_TYPE STATIC)
else()
    set(BUILD_TYPE SHARED)
endif()

add_library(${PROJECT_NAME} ${BUILD_TYPE}
    Athena/src/exceptions/badStreamException.h
    Athena/src/exceptions/compressionException.h
    Athena/src/exceptions/indexBoundsException.h

    Athena/src/streams/compression/compressedBuffer.cpp
    Athena/src/streams/compression/compressedBuffer.h

    Athena/src/streams/readers/fileStreamReader.h
    Athena/src/streams/readers/fileStreamReader.cpp
    Athena/src/streams/readers/streamReader.h

    Athena/src/streams/writers/fileStreamWriter.h
    Athena/src/streams/writers/fileStreamWriter.cpp
    Athena/src/streams/writers/streamWriter.h

    Athena/src/util/buffer.cpp
    Athena/src/util/buffer.h

    Athena/src/athena.h
    Athena/src/core.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC lz4::lz4)
target_include_directories(${PROJECT_NAME} PUBLIC Athena/src)

if(ATHENA_BUILD_EXAMPLE)
    find_package(raylib CONFIG REQUIRED)

    add_executable(AthenaSandbox
        sandbox/src/sandbox.cpp
    )

    target_link_libraries(AthenaSandbox PUBLIC Athena raylib)
    target_include_directories(AthenaSandbox PUBLIC Athena/src)
    set_property(TARGET AthenaSandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sandbox")
endif()