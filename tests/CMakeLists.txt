include(GoogleTest)
add_subdirectory("/home/david/gaia/Sources/GoogleBenchmark/benchmark/googletest" "/home/david/gaia/Sources/GoogleBenchmark/benchmark/googletest")

mark_as_advanced(
  BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
  gmock_build_tests gtest_build_samples gtest_build_tests
  gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
  )

# Don't add the testframe to the IDE
set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

# Simple macro, mostly for storage and comparison
macro(package_add_test TESTNAME)
  # create an exectuable in which the tests will be stored
  add_executable(${TESTNAME} ${ARGN})
  # link the Google test infrastructure, mocking library, and a default main fuction to
  # the test executable.  Remove g_test_main if writing your own main function.
  target_link_libraries(${TESTNAME} gtest gmock gtest_main)
  # gtest_discover_tests replaces gtest_add_tests,
  # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
  gtest_discover_tests(${TESTNAME}
    # set a working directory so your project root so that you can find test data via paths relative to the project root
    WORKING_DIRECTORY ${PROJECT_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
  set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()


# Library testing macro
macro(package_add_test_with_libraries TESTNAME FILES LIBRARIES TEST_WORKING_DIRECTORY)
  add_executable(${TESTNAME} ${FILES})
  target_link_libraries(${TESTNAME} gtest gmock gtest_main ${LIBRARIES})
  gtest_discover_tests(${TESTNAME}
    WORKING_DIRECTORY ${TEST_WORKING_DIRECTORY}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}"
    )
  set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

message("lib name: ${lib_name}")
package_add_test_with_libraries(test1 test1.cpp ${lib_name} ${PROJECT_SOURCE_DIR})

add_executable(runtest runtest.cpp)
target_link_libraries(runtest ${lib_name})
