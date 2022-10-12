cmake_minimum_required(VERSION 3.10)
  
project(perf-utils VERSION 1.0)

# Export compilation commands.
# The purpose here is to make retrieving optimisation options easier.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


set(CMAKE_CXX_STANDARD_REQUIRED true)

set(src_dir src)
set(inc_dir include)
#set(lib_dir lib)

set(perf-utils_files
  )

add_subdirectory(test)
