#include "stdio.h"
#include "spi.h"
#include "rpi_spi.h"

#include "bcm2835.h"

void rpi_spi_config(rpi_spi_t *config);

void spi_close() {
    rpi_spi_close();
}

spi_result spi_init(spi_channel_t channel, spi_mode_t mode, int freq, spi_endianess_t endianess) {
    rpi_spi_t spi = {
            .ce = CE0,
            .mode = mode,
            .bit_order = endianess,
            .clock_divider = BCM2835_SPI_CLOCK_DIVIDER_65536, // FIXME map freq to divider
            .polarity = RPI_SPI_LOW
    };

    switch (channel) {
        case SPI_CH_0:
            spi.ce = CE0;
            break;
        case SPI_CH_1:
            spi.ce = CE1;
            break;
        default:
            return SPI_NOT_SUPPORTED_ERROR;
    }

    return rpi_spi_init(&spi);
}

spi_result spi_transfer(char *data_out, char *data_in, uint8_t size) {
    return rpi_spi_transfer(data_out, data_in, size);
}

spi_result rpi_spi_transfer(uint8_t *data_out, uint8_t *data_in, int size) {
    if (!bcm2835_spi_begin()) {
        printf("bcm2835_spi_begin failed.\n");
        return SPI_TRANSACTION_ERROR;
    }

    bcm2835_spi_transfernb(data_out, data_in, size);

    bcm2835_spi_end();
}

spi_result rpi_spi_init(rpi_spi_t *spi) {
    if (!bcm2835_init()) {
        printf("bcm2835_init failed.\n");
        return SPI_DEVICE_ERROR;
    }

    rpi_spi_config(spi);

    return SPI_OK;
}

void rpi_spi_close() {
    bcm2835_close();
}

void rpi_spi_config(rpi_spi_t *config) {
    if (config->bit_order == SPI_MSB) {
        bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    } else {
        bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);
    }

    switch (config->mode) {
        case SPI_MODE_0:
            bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
            break;
        case SPI_MODE_1:
            bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);
            break;
        case SPI_MODE_2:
            bcm2835_spi_setDataMode(BCM2835_SPI_MODE2);
            break;
        case SPI_MODE_3:
            bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);
            break;
    }

    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);

    bcm2835SPIChipSelect ce;

    if (config->ce == CE0) {
        ce = BCM2835_SPI_CS0;
        bcm2835_spi_chipSelect(ce);
    } else {
        ce = BCM2835_SPI_CS1;
        bcm2835_spi_chipSelect(ce);
    }

    if (config->polarity == RPI_SPI_LOW) {
        bcm2835_spi_setChipSelectPolarity(ce, LOW);
    } else {
        bcm2835_spi_setChipSelectPolarity(ce, HIGH);
    }
}





