
#target_sources(perfutils-tests
#  PRIVATE
#  main.c)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(perfutils-tests main.c)
