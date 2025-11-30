cmake_minimum_required(VERSION 3.18.0)
include_guard(GLOBAL)
project(sokoban)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)    

set(TARGET ${PROJECT_NAME})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../tiage" "tiage_build")

add_executable(${TARGET} 
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

# Include directories
target_include_directories(${TARGET}       
    PRIVATE  
        "${CMAKE_CURRENT_SOURCE_DIR}/../tiage/inc"   
)

if (WIN32)
    target_link_options(${TARGET} PRIVATE "/SUBSYSTEM:WINDOWS")
endif()

# Link the tiage library
target_link_libraries(${TARGET} PRIVATE tiage)
