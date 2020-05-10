#ifndef SX1278_GPIO_H
#define SX1278_GPIO_H


typedef enum {
    GPIO_OK = 0,
    ERROR_GPIO_INIT = 0x8000,
    ERROR_GPIO_INVALID_STATE = 1,
} gpio_result_t;

typedef enum {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
} gpio_pin_e;

typedef enum {
    GPIO_PIN_STATE_LOW = 0,
    GPIO_PIN_STATE_HIGH = 1,
} gpio_pin_state_e;

typedef enum {
    GPIO_PIN_DIRECTION_INPUT = 0,
    GPIO_PIN_DIRECTION_OUTPUT = 1,
} gpio_pin_direction_e;

gpio_result_t gpio_init();
gpio_result_t gpio_set_direction(gpio_pin_e pin, gpio_pin_direction_e direction);
gpio_result_t gpio_read(gpio_pin_e pin, gpio_pin_state_e *state);
gpio_result_t gpio_write(gpio_pin_e pin, gpio_pin_state_e state);
void gpio_close();

#endif //SX1278_GPIO_H
