cmake_minimum_required(VERSION 3.5)
project(sx1278 C)

include_directories(include lib/include)
add_subdirectory(lib)

set(CMAKE_C_STANDARD 99)

add_library(sx1278 src/hello.c)

add_executable(example examples/main.c)
target_link_libraries(example mpsse_spi)