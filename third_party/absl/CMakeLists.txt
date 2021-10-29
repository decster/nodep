file(GLOB_RECURSE nodep_absl_SRC CONFIGURE_DEPENDS "*.cc")

add_library(nodep_absl ${nodep_absl_SRC})

target_include_directories(nodep_absl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})