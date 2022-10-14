cmake_minimum_required(VERSION 3.10)
  
project(perf-utils VERSION 1.0)

# Export compilation commands.
# The purpose here is to make retrieving optimisation options easier.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


set(CMAKE_CXX_STANDARD_REQUIRED true)

set(src_dir src)
set(inc_dir include)
#set(lib_dir lib)

add_library(perf-utils INTERFACE)
target_include_directories(perf-utils INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${inc_dir}/>)

set(perf-utils_files
  )

add_subdirectory(test)

export(TARGETS perf-utils NAMESPACE perf-utils:: FILE "${lib_dir}/cmake/perf-utils/${target-scalar-name}-config.cmake")
