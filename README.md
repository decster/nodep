# nodep

C++ application starter template

The purpose of this repo is to make creating c++ demos easier, cause setup
dependencies in c++ is a pain, I really "hate" things like:

* xxx.h.in
* configure
* complex CMake magic

So all those are removed, config.h are pre-generated(for common x86-64 linux
like environment), the make process only compile all cc files and link.

This repo already include some common dependencies in source code form:

* abseil
* glog
* gtest
* nlohmann json
* opentelemetry

If you don't need some of the dependencies, just comment out "add_directory"
lines in CMakeLists.txt and delete corresponding directories, e.g.

```
add_subdirectory(third_party/absl)
add_subdirectory(third_party/glog)
#add_subdirectory(third_party/opentelemetry)

```

