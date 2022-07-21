cmake_minimum_required(VERSION 3.1)
project(mimu22BL_parser)

SET(CMAKE_CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_executable(mimu22BL_parser mimu_parser.c)