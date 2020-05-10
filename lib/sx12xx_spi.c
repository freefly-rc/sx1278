#include "sx12xx_spi.h"

spi_result sx12xx_get_reg(uint8_t reg, uint8_t *data) {
    char data_in[2] = {0};
    char data_out[2] = {0x7f & reg, 0};

    spi_transfer(data_out, data_in, 2);
    *data = data_in[1];

    return SPI_OK;
}

spi_result sx12xx_get_regnm(uint8_t reg, uint8_t *data_in, uint8_t msb, uint8_t lsb) {
    if((msb > 7) || (lsb > 7) || (lsb > msb)) {
        return(ERROR_INVALID_BIT_RANGE);
    }

    uint8_t raw_value = 0;
    sx12xx_get_reg(reg, &raw_value);
    *data_in = raw_value & ((0b11111111u << lsb) & (0b11111111u >> (7u - msb)));

    return SPI_OK;
}

spi_result sx12xx_set_regnm(uint8_t reg, uint8_t value, uint8_t msb, uint8_t lsb) {
    if((msb > 7) || (lsb > 7) || (lsb > msb)) {
        return(ERROR_INVALID_BIT_RANGE);
    }

    uint8_t current_value = 0u;
    sx12xx_get_reg(reg, &current_value);
    uint8_t mask = ~((0b11111111u << (msb + 1u)) | (0b11111111u >> (8u - lsb)));
    uint8_t new_value = (current_value & ~mask) | (value & mask);

    return sx12xx_set_reg(reg, new_value);
}

spi_result sx12xx_set_reg(uint8_t reg, uint8_t value) {
    uint8_t current_value = 0;
    sx12xx_get_reg(reg, &current_value);
    if (current_value == value)
        return SPI_OK;

    char data_in[2] = {0};
    char data_out[2] = {0x80 | reg, value};
    spi_transfer(data_out, data_in, 2);

    for (int i = 0; i < READ_MAX_VALIDATION_ATTEMPTS; ++i) {
        sx12xx_get_reg(reg, &current_value);
        if (current_value == value)
            return SPI_OK;
    }

    return ERROR_READ_REGISTER;
}
