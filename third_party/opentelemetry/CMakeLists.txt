file(GLOB_RECURSE nodep_opentelemetry_SRC CONFIGURE_DEPENDS "*.cc")

add_library(nodep_opentelemetry ${nodep_opentelemetry_SRC})

#target_include_directories(nodep_opentelemetry PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})