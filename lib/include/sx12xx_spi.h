#ifndef SX1278_SX12XX_SPI_H
#define SX1278_SX12XX_SPI_H

#include "spi.h"

#define READ_MAX_VALIDATION_ATTEMPTS 10

#define ERROR_READ_REGISTER -1
#define ERROR_INVALID_BIT_RANGE -11

spi_result sx12xx_set_reg(uint8_t reg, uint8_t value);
spi_result sx12xx_get_reg(uint8_t reg, uint8_t *data_in);

spi_result sx12xx_set_regnm(uint8_t reg, uint8_t value, uint8_t msb, uint8_t lsb);
spi_result sx12xx_get_regnm(uint8_t reg, uint8_t *data_in, uint8_t msb, uint8_t lsb);

#endif //SX1278_SX12XX_SPI_H
