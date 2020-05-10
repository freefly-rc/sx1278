#ifndef SX1278_SPI_H
#define SX1278_SPI_H

#include <stdint.h>

typedef uint16_t spi_result;
#define SPI_OK 0
#define SPI_DEVICE_ERROR -1
#define SPI_TRANSACTION_ERROR -2
#define SPI_NOT_SUPPORTED_ERROR -3


typedef enum {
    SPI_MODE_0 = 0,
    SPI_MODE_1 = 1,
    SPI_MODE_2 = 2,
    SPI_MODE_3 = 3,
} spi_mode_t;

typedef enum {
    SPI_CH_0,
    SPI_CH_1,
    SPI_CH_2,
    SPI_CH_3,
} spi_channel_t;

typedef enum {
    SPI_MSB,
    SPI_LSB,
} spi_endianess_t;

spi_result spi_init(spi_channel_t channel, spi_mode_t mode, int freq, spi_endianess_t endianess);

void spi_close();

spi_result spi_transfer(char *data_out, char *data_in, uint8_t size);

#endif //SX1278_SPI_H
