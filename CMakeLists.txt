cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(athena)

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
    athena/src/exceptions/badStreamException.h
    athena/src/exceptions/compressionException.h
    athena/src/exceptions/indexBoundsException.h

    athena/src/streams/compression/compressedBuffer.cpp
    athena/src/streams/compression/compressedBuffer.h

    athena/src/streams/readers/fileStreamReader.h
    athena/src/streams/readers/fileStreamReader.cpp
    athena/src/streams/readers/streamReader.h

    athena/src/streams/writers/fileStreamWriter.h
    athena/src/streams/writers/fileStreamWriter.cpp
    athena/src/streams/writers/streamWriter.h

    athena/src/util/buffer.cpp
    athena/src/util/buffer.h

    athena/src/athena.h
    athena/src/core.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC lz4::lz4)
target_include_directories(${PROJECT_NAME} PUBLIC athena/src)

if(ATHENA_BUILD_EXAMPLE)
    find_package(raylib CONFIG REQUIRED)

    add_executable(athena-sandbox
        sandbox/src/sandbox.cpp
    )

    target_link_libraries(athena-sandbox PUBLIC athena raylib)
    target_include_directories(athena-sandbox PUBLIC athena/src)
    set_property(TARGET athena-sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sandbox")
endif()