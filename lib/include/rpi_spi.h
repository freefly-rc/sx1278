#ifndef SX1278_RPI_SPI_H
#define SX1278_RPI_SPI_H

#include "spi.h"


typedef enum {
    CE0,
    CE1
} rpi_spi_ce;

typedef enum {
    RPI_SPI_LOW,
    RPI_SPI_HIGH,
} rpi_spi_polarity;

typedef struct {
    spi_endianess_t bit_order;
    rpi_spi_ce ce;
    spi_mode_t mode;
    int clock_divider;
    rpi_spi_polarity polarity;
} rpi_spi_t;

spi_result rpi_spi_init(rpi_spi_t *spi);
void rpi_spi_close();

spi_result rpi_spi_transfer(uint8_t *data_out, uint8_t *data_in, int size);

#endif //SX1278_RPI_SPI_H
