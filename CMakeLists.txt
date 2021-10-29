cmake_minimum_required(VERSION 3.12)

# set the project name
project(nodep)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-g -DHAVE_ABSEIL=1")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-march=native -O3 -DNDEBUG" )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

add_subdirectory(third_party/absl)
add_subdirectory(third_party/glog)
add_subdirectory(third_party/opentelemetry)

add_executable(nodep
    src/main.cc
)

target_link_libraries(nodep
    nodep_opentelemetry
    nodep_absl
    nodep_glog
    -lcurl
    -pthread
    -lrt
)


add_subdirectory(third_party/gtest)

add_executable(nodep-test
    src/test-main.cc
)

target_link_libraries(nodep-test
    nodep_gtest
    nodep_absl
    nodep_glog
    -lcurl
    -pthread
    -lrt
)
