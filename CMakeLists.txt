cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(BSTMap)

add_executable(BSTMap
    main.cpp
)

target_include_directories(BSTMap
    PRIVATE ${PROJECT_SOURCE_DIR}
)