cmake_minimum_required(VERSION 3.15)
project(minerva-sandbox)

find_package(raylib CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    src/sandbox.cc
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    minerva
    raylib
)

set_property(TARGET ${PROJECT_NAME}
    PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)