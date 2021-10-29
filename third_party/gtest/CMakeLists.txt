file(GLOB_RECURSE nodep_gtest_SRC CONFIGURE_DEPENDS "*.cc")

add_library(nodep_gtest ${nodep_gtest_SRC})

target_include_directories(nodep_gtest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})