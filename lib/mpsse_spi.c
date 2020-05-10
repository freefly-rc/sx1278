#include "spi.h"

#include "mpsse.h"
#include "stdio.h"
#include "string.h"

struct mpsse_context *mpsse = NULL;
struct mpsse_context *gpio = NULL;

inline static enum modes to_mpsse_mode(spi_mode_t mode);
inline static int to_mpsse_endianess(spi_endianess_t endianess);
inline static enum gpio_pins to_mpsse_channel(spi_channel_t channel);

enum gpio_pins cs;

int spi_init(spi_channel_t channel, spi_mode_t mode, int freq, spi_endianess_t endianess) {
    mpsse = MPSSE(to_mpsse_mode(mode), freq, to_mpsse_endianess(endianess));
    gpio = MPSSE(GPIO, 0, 0);

    cs = to_mpsse_channel(channel);
    PinHigh(gpio, cs);

    if (mpsse != NULL && mpsse->open) {
        return 0;
    }

    printf("Failed to open spi: %s\n", ErrorString(mpsse));
    return 1;
}

void spi_close() {
    Stop(mpsse);
    Close(mpsse);
    mpsse = NULL;
}

void spi_begin_transaction() {
    PinLow(gpio, cs);
    Start(mpsse);
}

void spi_end_transaction() {
    Stop(mpsse);
    PinHigh(gpio, cs);
}

void spi_transfer(char *data_out, char *data_in, uint8_t size) {
    spi_begin_transaction();

    char *d = Transfer(mpsse, data_out, size);
    for (int i = 0; i < size; ++i) {
        data_in[i] = d[i];
    }

    spi_end_transaction();
}

inline static enum gpio_pins to_mpsse_channel(spi_channel_t channel) {
    switch (channel) {
        case SPI_CH_0:
            return GPIOH0;
        case SPI_CH_1:
            return GPIOH1;
        case SPI_CH_2:
            return GPIOL2;
        case SPI_CH_3:
            return GPIOH3;
        default:
            return GPIOH0;
    }
}

inline static enum modes to_mpsse_mode(spi_mode_t mode) {
    switch (mode) {
        case SPI_MODE_0:
            return SPI0;

        case SPI_MODE_1:
            return SPI1;

        case SPI_MODE_2:
            return SPI2;

        case SPI_MODE_3:
            return SPI3;

        default:
            return SPI0;
    }
}

inline static int to_mpsse_endianess(spi_endianess_t endianess) {
    switch (endianess) {
        case SPI_MSB:
            return MSB;
        case SPI_LSB:
            return LSB;
        default:
            return MSB;
    }
}
