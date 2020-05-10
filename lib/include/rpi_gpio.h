#include <stdint.h>

#ifndef SX1278_SPI_GPIO_H
#define SX1278_SPI_GPIO_H

#include "gpio.h"
#include "bcm2835.h"

typedef enum {
    GPIO05 = RPI_V2_GPIO_P1_29, // Mapped to GPIO0
    GPIO06 = RPI_V2_GPIO_P1_31, // Mapped to GPIO1
    GPIO12 = RPI_V2_GPIO_P1_32, // Mapped to GPIO2
    GPIO13 = RPI_V2_GPIO_P1_33, // Mapped to GPIO3
    GPIO19 = RPI_V2_GPIO_P1_35, // Mapped to GPIO4
    GPIO16 = RPI_V2_GPIO_P1_36, // Mapped to GPIO5
    GPIO26 = RPI_V2_GPIO_P1_37, // Mapped to GPIO6
    GPIO20 = RPI_V2_GPIO_P1_38, // Mapped to GPIO7
} rpi_gpio_pin_e;

gpio_result_t rpi_gpio_init();
gpio_result_t rpi_gpio_set_direction(rpi_gpio_pin_e pin, uint8_t direction);
gpio_result_t rpi_gpio_read(rpi_gpio_pin_e pin, gpio_pin_state_e *state);
gpio_result_t rpi_gpio_write(rpi_gpio_pin_e pin, uint8_t state);
void rpi_gpio_close();

#endif //SX1278_SPI_GPIO_H
