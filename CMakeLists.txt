cmake_minimum_required(VERSION 3.11)
project(AlgoLib
    VERSION 0.0.1)
enable_testing()

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "Disallow fallback when required C++ std is not available.")

file (GLOB_RECURSE TEST_FILES
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/*.cc"
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

foreach(file ${TEST_FILES})
    get_filename_component(test_name ${file} NAME_WE)
    add_executable(${test_name} ${file})
    add_test(NAME ${test_name}_run COMMAND ${test_name})
endforeach()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(asyncExecution_test PRIVATE Threads::Threads)
