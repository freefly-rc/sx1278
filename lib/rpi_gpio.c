#include "rpi_gpio.h"

rpi_gpio_pin_e map_rpi_gpio_pin(gpio_pin_e pin);
uint8_t map_rpi_gpio_direction(gpio_pin_direction_e direction);

gpio_result_t gpio_init() {
    return rpi_gpio_init();
}

gpio_result_t gpio_set_direction(gpio_pin_e pin, gpio_pin_direction_e direction) {
    rpi_gpio_pin_e rpi_pin = map_rpi_gpio_pin(pin);
    uint8_t rpi_dir = map_rpi_gpio_direction(direction);

    return rpi_gpio_set_direction(rpi_pin, rpi_dir);
}

gpio_result_t gpio_read(gpio_pin_e pin, gpio_pin_state_e *state) {
    rpi_gpio_pin_e rpi_pin = map_rpi_gpio_pin(pin);

    return rpi_gpio_read(rpi_pin, state);
}

gpio_result_t gpio_write(gpio_pin_e pin, gpio_pin_state_e state) {
    uint8_t on = 0;
    if (state == GPIO_PIN_STATE_LOW) {
        on = LOW;
    } else if (state == GPIO_PIN_STATE_HIGH) {
        on = HIGH;
    } else {
        return ERROR_GPIO_INVALID_STATE;
    }

    rpi_gpio_pin_e rpi_pin = map_rpi_gpio_pin(pin);

    return rpi_gpio_write(rpi_pin, on);
}

void gpio_close() {
    rpi_gpio_close();
}

gpio_result_t rpi_gpio_init() {
    if (!bcm2835_init()) {
        return ERROR_GPIO_INIT;
    }

    return GPIO_OK;
}

gpio_result_t rpi_gpio_set_direction(rpi_gpio_pin_e pin, uint8_t direction) {
    bcm2835_gpio_fsel((uint8_t) pin, direction);

    return GPIO_OK;
}

gpio_result_t rpi_gpio_read(rpi_gpio_pin_e pin, gpio_pin_state_e *state) {
    *state = (gpio_pin_state_e) bcm2835_gpio_lev((uint8_t) pin);

    return GPIO_OK;
}

gpio_result_t rpi_gpio_write(rpi_gpio_pin_e pin, uint8_t state) {
    bcm2835_gpio_write((uint8_t) pin, state);

    return GPIO_OK;
}


void rpi_gpio_close() {
    bcm2835_close();
}

/*
 *  GPIO    -->    RPI     PIN HEADER
 *  0              GPIO05  P1-29
 *  1              GPIO06  P1-31
 *  2              GPIO12  P1-32
 *  3              GPIO13  P1-33
 *  4              GPIO19  P1-35
 *  5              GPIO16  P1-36
 *  6              GPIO26  P1-37
 *  7              GPIO20  P1-38
 */
rpi_gpio_pin_e map_rpi_gpio_pin(gpio_pin_e pin) {
    switch (pin) {
        case GPIO_PIN_0:
            return GPIO05;
        case GPIO_PIN_1:
            return GPIO06;
        case GPIO_PIN_2:
            return GPIO12;
        case GPIO_PIN_3:
            return GPIO13;
        case GPIO_PIN_4:
            return GPIO19;
        case GPIO_PIN_5:
            return GPIO16;
        case GPIO_PIN_6:
            return GPIO26;
        case GPIO_PIN_7:
            return GPIO20;

        default:
            return GPIO05;
    }
}

uint8_t map_rpi_gpio_direction(gpio_pin_direction_e direction) {
    switch (direction) {
        case GPIO_PIN_DIRECTION_INPUT:
            return BCM2835_GPIO_FSEL_INPT;

        case GPIO_PIN_DIRECTION_OUTPUT:
            return BCM2835_GPIO_FSEL_OUTP;

        default:
            return BCM2835_GPIO_FSEL_INPT;
    }

}
