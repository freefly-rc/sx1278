cmake_minimum_required(VERSION 3.5)
project(sx1278 C CXX)
enable_testing()
add_subdirectory(tests)

include_directories(include lib/include)
add_subdirectory(lib)

set(CMAKE_C_STANDARD 99)

add_library(sx1278 src/sx1278.c include/sx1278.h)
target_link_libraries(sx1278 sx12xx_spi sx12xx_gpio)

add_executable(example examples/main.c)
target_link_libraries(example sx1278)
