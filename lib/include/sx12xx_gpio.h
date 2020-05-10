#ifndef SX1278_SX12XX_GPIO_H
#define SX1278_SX12XX_GPIO_H

#include "gpio.h"
#include "stdint.h"

gpio_result_t sx12xx_dio_init();
uint8_t sx12xx_dio_read();

#endif //SX1278_SX12XX_GPIO_H
