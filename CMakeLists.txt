cmake_minimum_required(VERSION 3.16)

set(lib_name armadilloWrapper)

project(${lib_name}
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 17)

# Configure the armadillo library
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
find_package(Threads REQUIRED)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# Build the library file
add_library(${lib_name} STATIC ${PROJECT_SOURCE_DIR}/src/Random.cpp) ## ${lib_source})
target_include_directories(${lib_name} PUBLIC
  ${PROJECT_SOURCE_DIR}/inc/
  ${PROJECT_SOURCE_DIR}/src/
  )

target_compile_options(${lib_name} BEFORE
  PRIVATE
  "$<$<CONFIG:Debug>:-Wall>"
  "$<$<CONFIG:Debug>:-ggdb>"

  "$<$<CONFIG:Test>:-Wall>"

  "$<$<CONFIG:Release>:-O3>"

  "$<$<CONFIG:Bench>:-O3>"
  )

# Ensure user defines type -- Could be Release by default
if(NOT CMAKE_BUILD_TYPE)
  message(FATAL_ERROR "Must define -DCMAKE_BUILD_TYPE=***")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  message("Configuring in Debug mode")
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
  message("Configuring in Debug mode")
  # Create install method
elseif(CMAKE_BUILD_TYPE STREQUAL Test)
  message("Configuring in Test mode")
  add_subdirectory(tests)

elseif(CMAKE_BUILD_TYPE STREQUAL Bench)
  message("Configuring in Bench mode")
  add_subdirectory(bench)
endif()

# if(debug)
#   message("Building library in debug mode")
#   target_compile_options(${lib_name} PRIVATE
#     "-ggdb"
#     )
#   # Add the DEBUG flag
#   add_compile_options("-DDEBUG")
#   set(release OFF)
# endif()

# if(bench)
#   message("Building benchmark tests")
#   include(GoogleTest)
#   add_subdirectory(bench)
# endif()

# if(test)
#   message("Building tests using testing framework")
#   enable_testing()
#   include(GoogleTest)
#   add_subdirectory(tests)
# endif()

# if(NOT debug)
#   if(release)
#     message("Building library in release mode")
#     target_compile_options(${lib_name} INTERFACE
#       " -O3"
#       )
#   endif()
# endif()

# target_link_libraries(${lib_name} PRIVATE ${ARMADILLO_LIBRARIES})
