#ifndef SX1278_SPI_H
#define SX1278_SPI_H

typedef enum {
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3,
} spi_mode_t;

typedef enum {
    SPI_CH_0,
    SPI_CH_1,
} spi_channel_t;

typedef enum {
    SPI_MSB,
    SPI_LSB,
} spi_endianess_t;

int spi_init(spi_channel_t channel, spi_mode_t mode, int freq, spi_endianess_t endianess);

void spi_stop();

char *spi_transfer(char *buff, int size);

#endif //SX1278_SPI_H
