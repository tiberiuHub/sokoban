cmake_minimum_required(VERSION 3.18.0)
include_guard(GLOBAL)
project(sokoban)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)    

set(TARGET ${PROJECT_NAME})

add_subdirectory("D:/work/tiage" "tiage_build")

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
        "D:/work/tiage/inc"   
)

# Link the tiage library
target_link_libraries(${TARGET} PRIVATE tiage)
