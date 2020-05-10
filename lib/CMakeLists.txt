include_directories(include)

#add_library(mpsse_spi SHARED mpsse_spi.c include/spi.h)
#target_link_libraries(mpsse_spi mpsse)

add_library(rpi_spi rpi_spi.c include/rpi_spi.h include/spi.h)
target_link_libraries(rpi_spi bcm2835)

add_library(rpi_gpio rpi_gpio.c include/rpi_gpio.h include/gpio.h)
target_link_libraries(rpi_gpio bcm2835)

add_library(sx12xx_gpio sx12xx_gpio.c include/gpio.h)
target_link_libraries(sx12xx_gpio rpi_gpio)

add_library(sx12xx_spi sx12xx_spi.c include/sx12xx_spi.h)
target_link_libraries(sx12xx_spi rpi_spi)
