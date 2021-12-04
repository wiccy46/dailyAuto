cmake_minimum_required(VERSION 3.10.0)
project(autogit VERSION ${CMAKE_PROJECT_VERSION})

add_subdirectory(autogit_lib)

set(AUTOGIT_SOURCES main.cpp)
set(SOURCES ${AUTOGIT_SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
    autogit_lib
    PUBLIC CONAN_PKG::boost
)
