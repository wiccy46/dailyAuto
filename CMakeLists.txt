cmake_minimum_required(VERSION 3.10.0)
project(autogit-top VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)
enable_testing()


set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(AUTOGIT_HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
set(HEADER_DIR ${AUTOGIT_HEADER_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include_directories(${HEADER_DIR})
conan_basic_setup(TARGETS)

add_subdirectory(autogit)
