#include "sx12xx_gpio.h"

gpio_result_t sx12xx_dio_init() {
    gpio_result_t result = GPIO_OK;

    result |= gpio_set_direction(GPIO_PIN_0, GPIO_PIN_DIRECTION_INPUT);
    result |= gpio_set_direction(GPIO_PIN_1, GPIO_PIN_DIRECTION_INPUT);
    result |= gpio_set_direction(GPIO_PIN_2, GPIO_PIN_DIRECTION_INPUT);
    result |= gpio_set_direction(GPIO_PIN_3, GPIO_PIN_DIRECTION_INPUT);
    result |= gpio_set_direction(GPIO_PIN_4, GPIO_PIN_DIRECTION_INPUT);
    result |= gpio_set_direction(GPIO_PIN_5, GPIO_PIN_DIRECTION_INPUT);
    result |= gpio_set_direction(GPIO_PIN_6, GPIO_PIN_DIRECTION_INPUT);
    result |= gpio_set_direction(GPIO_PIN_7, GPIO_PIN_DIRECTION_INPUT);

    return result;
}

/**
 * Read all GPIOs until one of them becomes 1 (HIGH)
 *
 * @return a byte indicating the pin number detected as HIGH
 */
uint8_t sx12xx_dio_read() {
    gpio_result_t result = GPIO_OK;
    uint8_t all_pin_state = 0;
    while (!all_pin_state) {
        for (int pin = GPIO_PIN_0; pin <= GPIO_PIN_7 ; ++pin) {
            gpio_pin_state_e current_state = GPIO_PIN_STATE_LOW;
            result |= gpio_read(pin, &current_state);
            all_pin_state |= (current_state << pin);
        }
    }

    return all_pin_state;
}
