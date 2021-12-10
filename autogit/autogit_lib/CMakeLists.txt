cmake_minimum_required(VERSION 3.10.0)
project(autogit_lib)


set(HEADERS
  include/autogit/helpers.hpp
  include/autogit/roam/Update.hpp
  )

set(SOURCES
  src/autogit/helpers.cpp
  src/autogit/roam/Update.cpp
  )

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
                      PUBLIC CONAN_PKG::boost
  )

target_include_directories(${PROJECT_NAME}
                           PUBLIC include ${PROJECT_BINARY_DIR}/include
  )

