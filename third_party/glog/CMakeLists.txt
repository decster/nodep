file(GLOB_RECURSE nodep_glog_SRC CONFIGURE_DEPENDS "*.cc")

add_library(nodep_glog ${nodep_glog_SRC})

target_include_directories(nodep_glog PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})