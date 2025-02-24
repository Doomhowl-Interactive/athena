cmake_minimum_required(VERSION 3.15)
project(minerva)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(MINERVA_BUILD_EXAMPLE "Build the example" OFF)

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
    minerva/src/exceptions/badStreamException.h
    minerva/src/exceptions/compressionException.h
    minerva/src/exceptions/indexBoundsException.h

    minerva/src/streams/compression/compressedBuffer.cpp
    minerva/src/streams/compression/compressedBuffer.h

    minerva/src/streams/readers/fileStreamReader.h
    minerva/src/streams/readers/fileStreamReader.cpp
    minerva/src/streams/readers/streamReader.h

    minerva/src/streams/writers/fileStreamWriter.h
    minerva/src/streams/writers/fileStreamWriter.cpp
    minerva/src/streams/writers/streamWriter.h

    minerva/src/util/buffer.cpp
    minerva/src/util/buffer.h

    minerva/src/minerva.h
    minerva/src/core.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC lz4::lz4)
target_include_directories(${PROJECT_NAME} PUBLIC minerva/src)

if(MINERVA_BUILD_EXAMPLE)
    find_package(raylib CONFIG REQUIRED)

    add_executable(minerva-sandbox
        sandbox/src/sandbox.cpp
    )

    target_link_libraries(minerva-sandbox PUBLIC minerva raylib)
    target_include_directories(minerva-sandbox PUBLIC minerva/src)
    set_property(TARGET minerva-sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sandbox")
endif()