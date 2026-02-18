cmake_minimum_required(VERSION 3.18.0)
project(sokoban)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)    

set(TARGET ${PROJECT_NAME})

set(TIAGE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../tiage")
add_subdirectory(${TIAGE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/tiage_build")

set(WIN32_EXECUTABLE TRUE)

add_executable(${TARGET} WIN32
    "${CMAKE_CURRENT_SOURCE_DIR}/Floor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Floor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Game.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Object.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Warehouse.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Warehouse.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

# Include tiage headers
target_include_directories(${TARGET}       
    PRIVATE  
        "${TIAGE_DIR}/inc"   
)

# Link the tiage library
target_link_libraries(${TARGET} PRIVATE tiage)