cmake_minimum_required(VERSION 3.16)
set(lib_name armadilloWrapper)
project(${name}
  LANGUAGES CXX)

# Set variables
set(debug OFF CACHE BOOL OFF)
set(bench OFF CACHE BOOL OFF)
set(test OFF CACHE BOOL OFF)
set(release ON CACHE BOOL ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -march=native")

# Configure the armadillo library
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
find_package(Threads REQUIRED)

include_directories(
	${PROJECT_SOURCE_DIR}/inc/
	${PROJECT_SOURCE_DIR}/src/
)

# Set the library source files
set(lib_source
	${PROJECT_SOURCE_DIR}/src/Random.cpp
  )


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# Build the library file
add_library(${lib_name} STATIC ${lib_source})

if(debug)
  message("Building library in debug mode")
  target_compile_options(${lib_name} PRIVATE
    "-ggdb"
    )
  # Add the DEBUG flag
  add_compile_options("-DDEBUG")
  set(release OFF)
endif()

if(bench)
  message("Building benchmark tests")
  include(GoogleTest)
  add_subdirectory(bench)
endif()

if(test)
  message("Building tests using testing framework")
  enable_testing()
  include(GoogleTest)
  add_subdirectory(tests)
endif()

if(NOT debug)
  if(release)
    message("Building library in release mode")
    target_compile_options(${lib_name} INTERFACE
      " -O3"
      )
  endif()
endif()

target_link_libraries(${lib_name} PRIVATE ${ARMADILLO_LIBRARIES})
