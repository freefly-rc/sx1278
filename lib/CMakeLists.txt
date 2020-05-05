include_directories(include)

add_library(mpsse_spi SHARED mpsse_spi.c include/spi.h)
target_link_libraries(mpsse_spi mpsse)